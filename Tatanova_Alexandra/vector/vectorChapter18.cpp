#include "vectorChapter18.h"

vector::vector() : sz{0}, elem {nullptr}, space{0} { }
vector::vector(int s)
    : sz{s}, elem{new double[s]}, space{s}
{
    for (int i = 0; i<sz; ++i)
        elem[i] = 0;
}

void vector::reserve(int newalloc)
{
    if ( newalloc <= space )
        return;
    double* p = new double[newalloc];
    for ( int i = 0; i < sz; ++i )
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = newalloc;
}
void vector:: resize( int newsize )
{
    reserve( newsize );
    for (int i = sz; i < newsize; ++i)
        elem[i] = 0;
    sz = newsize;
}
void vector::push_back(double d)
{
    if (space == 0)
        reserve(8);
    else
        if (sz == space)
            reserve(2*space);
    elem[sz] = d;
    ++sz;
}
vector& vector :: operator= (const vector& a) // Делаем данный вектор копией а
{
    if (this == &a)
        return *this;
    if (a.sz <= space)
    {
        for (int i = 0; i < a.sz; ++i)
           elem[i] = a.elem[i]; // Копирование эелентов
        sz = a.sz;
        return *this;
    }
    double* p = new double [a.sz]; // Выделение памяти
    for (int i = 0; i < a.sz; ++i)
        p[i] = a.elem[i]; // Копирование эелентов
    delete[] elem; // Освобождение памяти
    space = sz = a.sz;
    elem = p; // Переназначение указателя
    return *this; // Возрат ссылки на себя

}
vector :: vector(vector&& a)
    :sz{a.sz}, elem{a.elem} // Копируем elem и sz из а
{
    a.sz = 0; // Делаем вектор а пустым
    a.elem = nullptr;
}
vector& vector:: operator= (vector&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}
