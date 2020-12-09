#include "vector3.h"
// RAII захват ресурса есть инициализация Resource Acquisition Is Initialization
//Мы используем класс Range_error, чтобы облегчить отладку операции
//индексирования.
//Запутался между Vector и vector


// vector_base realisation

template<typename T, typename A>
vector_base<T, A>::vector_base():
    sz{0}, elem{alloc.allocate(0)}, space{0}{}

template<typename T, typename A>
vector_base<T, A>::vector_base(int s):
    sz{s}, elem{alloc.allocate(s)}, space{s}{}

template<typename T, typename A>
vector_base<T, A>::vector_base(const A& a, int s):
    alloc{a}, sz{s}, elem(alloc.allocate(s)), space{s}{}

//construcotr for () if we want vector(vector)
template<typename T, typename A>
vector_base<T, A>::vector_base(const vector_base& arg)
{
    T* p = alloc.allocate(arg.sz);
    for (int i=0; i<arg.sz; i++)
        alloc.construct(&p[i], arg.elem[i]);
    elem=p;
    sz=arg.sz;
    space=arg.space;
}

template<typename T, typename A> vector_base<T, A>::
vector_base(std::initializer_list<T> lst):
    sz{static_cast<int>(lst.size())}, elem{new T[sz]}, space{sz}
{
    copy(lst.begin(), lst.end(), elem);
}

template<typename T, typename A>
vector_base<T, A>:: ~vector_base()
{
    alloc.deallocate(elem, space);
}


// Vector realisation
// constructors and metods

template<typename T, typename A>
Vector<T, A> :: Vector(): vector_base<T, A>(){}

template<typename T, typename A>
Vector<T, A> :: Vector(int s) : vector_base<T, A>(s)
{
    for (int i=0; i<s; i++)
        this->alloc.construct(&this->elem[i], T());
}


template<typename T, typename A> Vector<T,A> ::
Vector(std::initializer_list<T> lst) : vector_base<T, A> (lst)
{
    // Инициализация с помощью std::copy ();
    copy(lst.begin(), lst.end(), this->elem); //за счёт этого делаем vector v1 = { 1,2,3 };
    /*Он (copy)
копирует последовательность элементов, определяемую первыми двумя
аргументами (в данном случае - начало и конец initiali zer_list)
в последовательность элементов, начало которой указывает
его третий аргумент (в данном случае - последовательность
элементов вектора, начинающаяся с elem). */
}

template<typename T, typename A> Vector<T, A> & Vector<T, A> ::
operator=(const Vector<T, A>& a)
{
    //первые 2 if для оптимизации, без них тоже должно работать
    if (this==&a) return *this; //Самоприсваивание, ничего делать не надо

    if (a.sz<=this->space)   //Памяти достаточно, новая
                             //память не нужна
    {
        for(int i=0; i<a.sz; i++)
            this->elem[i]=a.elem[i];  //Копируем элементы
        this->sz=a.sz;
        return *this;
    }
    T * p=this->alloc.allocate(this->sz); //new T[a.sz] //Выделяем новую память
    for (int i=0; i<a.sz; i++)
        p[i]=a.elem[i];        //Копируем элементы
    this->alloc.destroy(this->elem);           //освобождаем старую память
    this->space=this->sz=a.sz;           //Устанавливаем новый размер
    this->elem=p;                  //устанавливаем указатель на новые элементы
    return *this;            //возвращаем ссылку на себя
}

template<typename T, typename A> Vector<T,A>::Vector(Vector<T, A> && a)
// Копируем elem и sz из а
{
    this-> sz=a.sz;
    this-> elem=a.elem;
    this-> space=this->sz;
    a.sz=0;         //Делаем вектор а пустым
    a.elem=nullptr;
    a.space=a.sz;
}

template<typename T, typename A>Vector<T,A> ::
Vector(const Vector<T, A>& arg) : vector_base<T, A>(arg) {}

template<typename T, typename A>Vector<T,A>& Vector<T,A> ::
operator=(Vector<T, A> && a) //Перемещаем а в текущий вектор
{
    this->alloc.destroy(this->elem);// Освобождение старой памяти
    this->elem=a.elem;  // Копирование elem и sz из а
    this->sz=a.sz;
    a.elem=nullptr;  //делаем вектор пустым
    a.sz=0;
    return *this;   //Возврат ссылки на себя
}


template<typename T, typename A>void Vector<T,A>::reserve(int newalloc)
{
    if (newalloc<=this->space) return; //Размер никогда не уменьшается
    vector_base<T,A>
            new_base(this->alloc,newalloc); //Выделение новой памяти
    std::uninitialized_copy(this->elem, this->elem + this->sz, new_base.elem); //копирование new_base.elem, &new_base.elem[this->sz], this->elem

    for (int i=0; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]); //удаление старых объектов
    std::swap<vector_base<T,A>>(*this, new_base); //Обмен представлений

//    T *p=alloc.allocate(newalloc); //Выделение новвой памяти
//    //Копирование:
//    for (int i=0; i<sz; i++)
//        alloc.construct(&p[i], elem[i]);       //Копируем старые элементы
//    //Уничтожение:
//    for (int i=0; i<sz; i++)
//        alloc.destroy(&elem[i]);
//    alloc.deallocate(elem,space);        //Освобождаем старую память
//    elem=p;
//    space=newalloc;
}

template<typename T, typename A>void Vector<T,A>::resize(int newsize, T val) //, T val=T()
//Создаём вектор, содержащий newsize элементов
//Инициализируем каждый элемент значением по умолчанию 0.0
{
    reserve(newsize);
    //создаём
    for (int i=this->sz; i<newsize; i++)
        this->alloc.construct(&this->elem[i], val); //Инициализирует новые элемент
    //Уничтожаем:
    for (int i=newsize; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]);
    this->sz=newsize;
}

template<typename T, typename A>void Vector<T,A>::push_back(const T& val)
{
    if (this->space==0)
        reserve(8);                    //выделяем память для 8 элементов
    else if (this->sz==this->space)
        reserve(2 * this->space);      //Выделяем дополнительную память
    this->alloc.construct(&this-> elem[this-> sz], val);//Добавляем val в конец вектора
    ++this->sz;                        //Увеличиваем количество элементов (Размер)
}

//Проверка на вместимость
template<typename T, typename A> T& Vector<T,A>::at(int n)
{
    if ((n<0)||(this->sz<=n))
        throw Range_error(n);
    return this->elem[n];
}

template<typename T, typename A> int Vector<T, A>::size() const
{
    return this->sz;
}

template<typename T, typename A> T Vector<T, A>::get(int n) const
{
    return this->elem[n];
}

template<typename T, typename A> void Vector<T, A> :: set(int n, T t)
{
    this->elem[n]=t;
}

template<typename T, typename A> T& Vector<T,A>::operator[](int n)
{
    return at(n); //at было использовано, для проверки выхода из диапазона
}

template<typename T, typename A>int Vector<T,A> ::
capacity() const {return this->space;} //Сколько свободного места осталось

template<typename T, typename A> Vector<T, A>::~Vector() {}

template class Vector<double>;
template class Vector<int>;
template class Vector<char>;
template class Vector<string>;
template class Vector<float>;
