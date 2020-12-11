#include "vector3.h"
// RAII захват ресурса есть инициализация Resource Acquisition Is Initialization
//Мы используем класс Range_error, чтобы облегчить отладку операции
//индексирования.



// vector_base realisation

template<typename T, typename A>
vector_base<T, A>::vector_base():
    elem{nullptr}, sz{0}, space{0} { }

//перемещающий конструктор
template<typename T, typename A>
vector_base<T, A>::vector_base(vector_base && a):
    elem{a.elem}, sz{a.sz}, space{a.space}
{
    a.elem=nullptr;
    a.sz=0;
    a.space=0;
}

template<typename T, typename A>
vector_base<T, A>::vector_base(const A& a, size_t s):
    alloc{a}, elem{alloc.allocate(s)}, sz{s}, space{s} {}

template<typename T, typename A>vector_base<T,A>& vector_base<T,A> ::
operator=(vector_base<T, A> && a)
{
    for (size_t i=0; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]);
    this->alloc.deallocate(this->elem, this-> space);
    this->elem=a.elem;this->sz=a.sz;
    a.elem=nullptr;
    a.sz=0;
    return *this;
}



template<typename T, typename A>
vector_base<T, A>:: ~vector_base()
{
    alloc.deallocate(elem, space);
}


// Vector realisation
// constructors and metods

//Конструктор для вектора размером s
template<typename T, typename A>
Vector<T, A> :: Vector(size_t s) : vector_base<T, A>()
{ reserve(s); }

//конструктор списком инициализации
template<typename T, typename A> Vector<T,A> ::
Vector(std::initializer_list<T> lst) : vector_base<T, A> (A(), lst.size())
{
    // Инициализация с помощью std::copy ();
                                 //куда копируем
    uninitialized_copy(lst.begin(), lst.end(), this->elem); //за счёт этого делаем vector v1 = { 1,2,3 };
    /*Он (copy)
копирует последовательность элементов, определяемую первыми двумя
аргументами (в данном случае - начало и конец initiali zer_list)
в последовательность элементов, начало которой указывает
его третий аргумент (в данном случае - последовательность
элементов вектора, начинающаяся с elem). */
}

template<typename T, typename A> Vector<T, A> & Vector<T, A> ::
operator=(const Vector& a)
{
    //if для оптимизации, без него тоже должно работать
    if(this == &a) return *this;

    vector_base<T,A> p(A(), a.sz); //выделение новой памяти дефолтный конструктор
    uninitialized_copy(a.elem, &a.elem[a.sz], p.elem);

    for(size_t i = 0; i< this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);


    swap<vector_base<T,A>>(*this, p); //обмен представлений
    this->sz = a.sz;
    this->space = a.space;
    return *this;
}

//Перемещающий конструктор
template<typename T, typename A> Vector<T,A>::Vector(Vector<T, A> && a):
    vector_base<T, A>(static_cast<vector_base<T, A>&&>(a))
// Копируем elem и sz из а
{
//    this-> sz=a.sz;
//    this-> elem=a.elem;
//    this-> space=this->sz;
//    a.sz=0;         //Делаем вектор а пустым
//    a.elem=nullptr;
//    a.space=a.sz;
}

//Конструктор другим вектором, копирующая инициализация
template<typename T, typename A>Vector<T,A> ::
Vector(const Vector& arg) : vector_base<T, A>{A(), arg.size()}
{
    uninitialized_copy(arg.elem, &arg.elem[this->sz], this->elem);
}

//Перемещающее присваивание
template<typename T, typename A>Vector<T,A>& Vector<T,A> ::
operator=(Vector<T, A> && a) //Перемещаем а в текущий вектор
{
    for(size_t i = 0; i< this -> sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->alloc.deallocate(this->elem, this-> space);// Освобождение старой памяти
    this->elem=a.elem;  // Копирование elem и sz из а
    this->sz=a.sz;
    a.elem=nullptr;  //делаем вектор пустым
    a.sz=0;
    return *this;   //Возврат ссылки на себя
}

//выделить память на newalloc элементов и сохранить старые значения
template<typename T, typename A>void Vector<T,A>::reserve(size_t newalloc)
{
    if (newalloc <= this->space) return; //Размер никогда не уменьшается
    vector_base<T,A>
            new_base(this->alloc, newalloc); //Выделение новой памяти
    std::uninitialized_copy(this->elem, &this->elem[this->sz], new_base.elem); //копирование new_base.elem, &new_base.elem[this->sz], this->elem

    for (size_t i=0; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]); //удаление старых объектов

    std::swap<vector_base<T,A>>(*this, new_base); //Обмен представлений

    this->sz=new_base.sz;
    this->space=new_base.space;
}

template<typename T, typename A>
void Vector<T,A>::resize(size_t newsize, T val) //, T val=T()
//Создаём вектор, содержащий newsize элементов
//Инициализируем каждый элемент значением по умолчанию 0.0
{
    reserve(newsize);
    //создаём
    if(newsize < this->sz)
    {
        for(T* ptr = newsize; ptr < this->elem + this->sz; ++ptr)
            this->alloc.destroy(ptr);
        this->sz = newsize;
    }
    else
    {
        //аналог uninitialized_copy, сделан так, чтобы отлавливать ошибки, потому что может быть утечка памяти
        //ошибки могут быть у construct
        T* current = this->elem+this->sz;
        try
        {
           for (; current < this->elem + newsize; ++current)
               this->alloc.construct(current, T());
           this->sz=newsize;
        }
        catch (...)
        {
            for (T* ptr = this-> elem+ this->sz; ptr < current; ++ptr)
                this->alloc.destroy(ptr);
            throw;
        }
    }
}

template<typename T, typename A>void Vector<T,A>::push_back(const T& val)
{
    if (this->space==0)
        reserve(8);                    //выделяем память для 8 элементов
    else if (this->sz==this->space)
        reserve(2 * this->space);      //Выделяем дополнительную память
    uninitialized_fill(&this->elem[this->sz], &this->elem[this->sz]+1, val);//Добавляем val в конец вектора, поэтому +1
    ++this->sz;                        //Увеличиваем количество элементов (Размер)
}




template<typename T, typename A> T Vector<T, A>::get(int n) const
{
    return this->elem[n];
}

template<typename T, typename A> void Vector<T, A> :: set(int n, T t)
{
    this->elem[n]=t;
}

//Реализация деструктора. destroy сначала очищает то,
//что лежало в векторе
template<typename T, typename A> Vector<T, A>::~Vector()
{
    for(size_t i=0; i<this->sz; i++)
        this->alloc.destroy(&this->elem[i]);
}

