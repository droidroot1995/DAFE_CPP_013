//
// Created by Алексей Ячменьков.
//

#include "vecc.h"

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= space) return;   //Размер не уменьшается
    T* p = alloc.allocate(newalloc); //Выделяем новую память
    //Копирование:
    for (int i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);
    //Уничтожение:
    for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
    alloc.deallocate(elem,space); //Освобождаем старую память
    elem = p;
    space = newalloc;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T,A>::vector():sz{0}, elem{nullptr}, space{0} {}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T,A>::vector(int s)
:sz{s}, elem{new T[sz]}, space{sz}
{
    for (int i=0; i<s; ++i) elem[i] = T();
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::vector(std::initializer_list<T> lst):
sz{static_cast<int>(lst.size())}, elem{new T[sz]}, space{sz}
{
    std::copy(lst.begin(), lst.end(), elem);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> vector<T,A>::vector(const vector<T,A>& arg)
:sz{arg.sz}, elem{new T[arg.sz]}, space{sz}
{
    std::copy(arg.elem, arg.elem+sz, elem);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> vector<T,A>::vector(vector<T,A>&& a)
:sz{a.sz}, elem{a.elem}, space{sz}
{
    a.sz = 0;  //Делаем вектор a пустым
    a.elem = nullptr;
    a.space = a.sz;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> T& vector <T, A>::at(int n)
{
    if(0<=n && n <=sz)
        return elem[n];
    throw Out_range (n);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> vector<T, A>& vector<T,A>::operator=(vector<T,A>&& a)   //Перемещаем а в текущий вектор
{
    delete[] elem;     // Освобождение памяти
    elem = a.elem;     // Копирование elem и sz a
    sz = a.sz;
    a.sz = 0;
    a.elem = nullptr;
    return *this;      //Возврат ссылки на себя
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a)
{
    if (&a == this)
        return *this; // Самоприсваивание
    if (a.sz <= space)
    {
        for (int i = 0; i<a.sz; ++i)
            elem[i] = a.elem[i];  // Копируем элементы
        sz = a.sz;
        return *this;
    }
    T* p = new T[a.sz];  //Выделяем новую память
    for (int i = 0; i<a.sz; ++i)
        p[i] = a.elem[i]; //Копируем элементы
    delete[] elem; //Освобождаем старую память
    elem = p;
    space = sz = a.sz; //Устанавливаем указатель на новые элементы
    return *this;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
T& vector<T,A>::operator[](int n)
{
    if (0 <= n && n <= sz) return elem[n];
    throw Out_range(n);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
T vector<T,A>::operator[](int n) const
{
    if (0 <= n && n <= sz) return elem[n];
    throw Out_range(n);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
int vector<T,A>::size() const
{
    return sz;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> T vector<T,A>::get(int n) const
{
    return elem[n];
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> void vector<T,A>::set(int n, T t)
{
    elem[n]=t;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
void vector<T,A>::resize(int newsize, T val)
{
    reserve(newsize);
    //Создаем:
    for (int i=sz; i<newsize; ++i) alloc.construct(&elem[i],val);
    //Уничтожение:
    for(int i = sz; i < newsize; ++i) alloc.destroy(&elem[i]);
    sz = newsize;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
void vector<T,A>::push_back(const T& val)
{
    if (space == 0)
        reserve(8); //Начинаем с 8 элементов
    else if (sz == space)
        reserve(2*space); //Выделяем больше памяти
    alloc.construct(&elem[sz], val); //Добавляем в конец значение val

    ++sz; //Увеличиваем размер
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
int vector<T,A>::capacity() const
{
    return space;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A> vector<T,A>::~vector()
{
    delete[] elem;
}

//------------------------------------------------------------------------------------------------

template class vector<double>;
template class vector<int>;
template class vector<char>;
template class vector<std::string>;