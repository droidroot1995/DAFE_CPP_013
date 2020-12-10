//
// Created by Алексей Ячменьков.
//

#include "vecc.h"

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T,A>::vector_base()
:elem(alloc.allocate(0)), sz(0), space(0)
{}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T,A>::vector_base(int n)
:elem(alloc.allocate(n)), sz(n), space(n)
{}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T,A>::vector_base(const A& a, int n)
:alloc(a), elem(alloc.allocate(n)), sz(n), space(n)
{}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T, A>::vector_base(const vector_base& arg)
{
    T* p = alloc.allocate(arg.sz);
    for(int i=0; i<arg.sz; ++i)
        alloc.construct(&p[i], arg.elem[i]);
    elem = p;
    sz = arg.sz;
    space = arg.space;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T, A>::vector_base(std::initializer_list<T> lst)
:sz{static_cast<int>(lst.size())}, elem{new T[sz]}, space{sz}
{
    std::copy(lst.begin(), lst.end(), elem);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector_base<T, A>::~vector_base()
{
    alloc.deallocate(elem, space);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::vector()
:vector_base<T, A>() {}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::vector(int s)
:vector_base<T, A>(s)
{
    for (int i = 0; i < s; ++i)
        this->alloc.construct(&this->elem[i], T());
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::vector(std::initializer_list<T> lst)
:vector_base<T, A>(lst)
{
    std::copy(lst.begin(), lst.end(), this->elem);
}

//------------------------------------------------------------------------------------------------


template<typename T, typename A>
vector<T, A>::vector(const vector<T, A>& arg)
:vector_base<T, A>(arg)
{}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::vector(vector<T, A>&& a)
{
    this->sz = a.sz;
    this->elem = a.elem;
    this->space = this->sz;
    a.sz = 0;
    a.elem = nullptr;
    a.space = a.sz;
}

//------------------------------------------------------------------------------------------------

//память
template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space)
        return;
    vector_base<T, A> b(this->alloc, newalloc);
    std::uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
    for (int i=0; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    swap<vector_base<T, A>>(*this, b);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
    if (0 <= n && n <= this->sz)
        return this->elem[n];
    throw Out_range(n);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector<T, A>&& a)
{
    this->alloc.destroy(this->elem);
    this->elem = a.elem;
    this->sz = a.sz;
    a.sz = 0;
    a.elem = nullptr;
    return *this;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>& a)
{
    if (&a == this)
        return *this;
    if (a.sz <= this->space)
    {
        for (int i = 0; i<a.sz; ++i)
            this->elem[i] = a.elem[i];
        this->sz = a.sz;
        return *this;
    }
    T* p = this->alloc.allocate(this->sz);
    for (int i = 0; i<a.sz; ++i)
        p[i] = a.elem[i];
    this->alloc.destroy(this->elem);
    this->elem = p;
    this->space = this->sz = a.sz;
    return *this;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
T& vector<T, A>::operator[](int n)
{
    return at(n);
}

//------------------------------------------------------------------------------------------------


template<typename T, typename A>
T vector<T, A>::operator[](int n) const
{
    if (0 <= n && n <= this->sz)
        return this->elem[n];
    throw Out_range(n);
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
int vector<T, A>::size() const
{
    return this->sz;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
T vector<T, A>::get(int n) const
{
    return this->elem[n];
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
void vector<T, A>::set(int n, T t)
{
    this->elem[n]=t;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
void vector<T, A>::resize(int newsize, T val)
{
    reserve(newsize);
    for (int i = this->sz; i < newsize; ++i)
        this->alloc.construct(&this->elem[i], val);
    for (int i = this->sz; i < newsize; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->sz = newsize;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
void vector<T, A>::
push_back(const T& val)
{
    if (!this->space) reserve(8);
    else if (this->sz == this->space) reserve(2*this->space);
    this->alloc.construct(&this->elem[this->sz], val);
    ++this->sz;
}

//------------------------------------------------------------------------------------------------

template<typename T, typename A>
int vector<T, A>::capacity() const
{
    return this->space;
}


//------------------------------------------------------------------------------------------------

template<typename T, typename A>
vector<T, A>::~vector()
{}

//------------------------------------------------------------------------------------------------

template class vector<double>;
template class vector<int>;
template class vector<char>;
template class vector<std::string>;






//template<typename T>
//T* allocator<T>::allocate(int n)
//{
//    //c
//    //return static_cast<T*>(malloc(sizeof(T)*n));
//
//    //c++
//    return (new char[sizeof (T)*n]);
//}
//
////------------------------------------------------------------------------------------------------
//
//template<typename T>
//void allocator<T>::deallocate(T* p, int n)
//{
//    //c++
//    delete[] reinterpret_cast<char*>(p);
//}
//
////------------------------------------------------------------------------------------------------
//
//template<typename T>
//void allocator<T>::construct(T *p, const T &v)
//{
//    new (p) T(v);
//}
//
////------------------------------------------------------------------------------------------------
//
//template<typename T>
//void allocator<T>::destroy(T *p)
//{
//    p->~T();
//}