#include "vector3.h"
// RAII захват ресурса есть инициализация Resource Acquisition Is Initialization
//Мы используем класс Range_error, чтобы облегчить отладку операции
//индексирования.
//Запутался между Vector и vector

//struct Range_error:out_of_range //Расширенное сообщение о выходе
//{                               //за пределы диапазона
//    int index;
//    Range_error(int i):
//        out_of_range{"Range error"}, index{i}{}
//};

//template<typename T> struct Vector: public vector<T>
//{
//    using size_type=typename vector<T>::size_type;
//    using vector<T>::vector; //Использование конструкторов vector<T>

//    T&operator[](size_type i) //Вместо возврата at(i)
//    {
//        if (i<0||this->size()<=i)
//            throw Range_error(i);
//        return vector<T>::operator[](i);
//    }

//    const T& operator[](size_type i) const
//    {
//        if (i<0||this->size()<=i)
//            throw Range_error(i);
//        return vector<T>::operator[](i);
//    }
//};

template<typename T, typename A> vector<T,A>::vector(const initializer_list<T>& lst): //initializer_list<T> lst
    sz{ int(lst.size())},
    elem{new T[sz]} //Неинициализированная память
{

    // Инициализация с помощью std::copy ();
    copy(lst.begin(), lst.end(), elem); //за счёт этого делаем vector v1 = { 1,2,3 };
    /*Он (copy)
копирует последовательность элементов, определяемую первыми двумя
аргументами (в данном случае - начало и конец initiali zer_list)
в последовательность элементов, начало которой указывает
его третий аргумент (в данном случае - последовательность
элементов вектора, начинающаяся с elem). */
}

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a)
{
    //первые 2 if для оптимизации, без них тоже должно работать
    if (this==&a) return *this; //Самоприсваивание, ничего делать не надо

    if (a.sz<=space)   //Памяти достаточно, новая
                       //память не нужна
    {
        for(int i=0; i<a.sz; i++)
            elem[i]=a.elem[i];  //Копируем элементы
        sz=a.sz;
        return *this;
    }
    T*p=new T[a.sz]; //Выделяем новую память
    for (int i=0; i<a.sz; i++)
        p[i]=a.elem[i];        //Копируем элементы
    delete[] elem;           //освобождаем старую память
    space=sz=a.sz;           //Устанавливаем новый размер
    elem=p;                  //устанавливаем указатель на новые элементы
    return *this;            //возвращаем ссылку на себя
}

template<typename T, typename A> vector<T,A>::vector(vector<T,A>&& a)
    :sz{a.sz}, elem{a.elem} // Копируем elem и sz из а
{
    a.sz=0;         //Делаем вектор а пустым
    a.elem=nullptr;
}

template<typename T, typename A>vector<T,A>::vector(const vector<T,A>& arg)
    :sz{arg.sz}, elem{new T[arg.sz]} //Размещает элементы, инициализирует их копированием
{
    copy(arg.elem, arg.elem+arg.sz, elem);
}

//    for (int i = 0; i < sz; i++)
//    {
//        this->elem[i] = arg.elem[i];
//    }

template<typename T, typename A>vector<T,A>& vector<T,A>::operator=(vector<T,A>&& a) //Перемещаем а в текущий вектор
{
    delete[] elem;// Освобождение старой памяти
    elem=a.elem;  // Копирование elem и sz из а
    sz=a.sz;
    a.elem=nullptr;  //делаем вектор пустым
    a.sz=0;
    return *this;   //Возврат ссылки на себя
}


template<typename T, typename A>int vector<T,A>::capacity() const {return space;}

template<typename T, typename A>void vector<T,A>::reserve(int newalloc)
{
    if (newalloc<=this->space) return; //Размер никогда не уменьшается
    vector_base<T,A>
            b(this->alloc,newalloc); //Выделение новой памяти
    uninitialized_copy(b.elem, &b.elem[this->sz], this->elem); //копирование
    for (int i=0; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]); //удаление старых объектов
    swap<vector_base<T,A>>(*this,b); //Обмен представлений

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

template<typename T, typename A>void vector<T,A>::resize(int newsize, T val) //, T val=T()
//Создаём вектор, содержащий newsize элементов
//Инициализируем каждый элемент значением по умолчанию 0.0
{
    reserve(newsize);
    //создаём
    for (int i=sz; i<newsize; i++)
        alloc.construct(&elem[i], val); //Инициализирует новые элемент
    //Уничтожаем:
    for (int i=newsize; i<sz; i++)
        alloc.destroy(&elem[i]);
    sz=newsize;
}

template<typename T, typename A>void vector<T,A>::push_back(const T& val)
{
    if (space==0)
        reserve(8);      //выделяем память для 8 элементов
    else if (sz==space)
        reserve(2*space);//Выделяем дополнительную память
    alloc.construct(&elem[sz], val);//Добавляем val в конец вектора
    ++sz;                //Увеличиваем количество элементов (Размер)
}

template<typename T, typename A> T& vector<T,A>::at(int n)
{
    if (n<0||sz<=n)
        throw out_of_range("");
    return elem[n];
}


template<typename T, typename A> T& vector<T,A>::operator[](int n)
{
    return elem[n];
}
