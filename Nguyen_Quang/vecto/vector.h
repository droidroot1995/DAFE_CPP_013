#ifndef vector_h
#define vector_h

#include <iostream>
#include <memory>
#include <string>
#include "vectoBase.h"

template <typename T, typename A = std::allocator<T>>
class vector : private vector_base<T, A>
{

    A alloc;
    int sz;
    T *elem;
    int space;

    void copy(const vector &arg);

public:
    vector() : sz{0}, elem{nullptr}, space{0} {}
    explicit vector(int s) : sz{s}, elem{alloc.allocate(s)}, space{s}
    {
        for (int i = 0; i < sz; ++i)
            alloc.construct(elem + i, T());
    }
    vector(const vector &);
    vector &operator=(const vector &);

    ~vector()
    {
        for (int i = 0; i < sz; ++i)
        {
            alloc.destroy(elem + i);
        }
        alloc.deallocate(elem, sz);
    }

    T &at(int n);
    const T &at(int n) const;
    T &operator[](int n) { return elem[n]; }
    const T &operator[](int n) const { return elem[n]; };

    int size() const { return sz; }
    int capacity() const { return space; }

    void resize(int newsize, T val = T());
    void push_back(const T &d);
    void reserve(int newalloc);
};

template <class T, class A>
vector<T, A>::vector(const vector &arg)
    : sz{arg.sz}, space{arg.sz}, elem{alloc.allocate(arg.space)}
{
    copy(arg);
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(const vector &a)
{
    if (this == &a)
        return *this;
    if (a.sz <= space)
    {
        for (int i = 0; i < a.sz; ++i)
            elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }
    T *p = alloc.allocate(a.space);
    for (int i = 0; i < a.sz; i++)
        alloc.construct(&p[i], a.elem[i]);
    for (int i = 0; i < sz; i++)
        alloc.destroy(&elem[i]);

    alloc.deallocate(elem, space);
    space = sz = a.sz;
    elem = p;
    return *this;
}

template <class T, class A>
void vector<T, A>::copy(const vector &arg)
{
    for (int i = 0; i < arg.sz; i++)
        alloc.construct(elem + i, arg[i]);
}

template <typename T, typename A>
T &vector<T, A>::at(int n)
{
    if (n < 0 || sz <= n)
    {
        std::string s = "Wrong index";
        throw std::out_of_range(s);
    }
    return elem[n];
}

template <typename T, typename A>
const T &vector<T, A>::at(int n) const
{
    if (n < 0 || sz <= n)
    {
        std::string s = "Wrong index";
        throw std::out_of_range(s);
    }
    return elem[n];
}

template <typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{

    if (newalloc <= this->space)
        return;

    vector_base<T, A> b(this->alloc, newalloc);
    std::uninitialized_copy(elem, elem + sz, b.elem);
    b.sz = sz;
    T *temp = this->elem;
    int temp_space = this->space;
    this->space = newalloc;
    this->elem = b.elem;
    for (int i = 0; i < this->sz; ++i)
        this->alloc.destroy(temp + i);
    b.elem = temp;
    b.space = temp_space;
}

template <typename T, typename A>
void vector<T, A>::resize(int newsize, T val) //
{
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        alloc.construct(elem + i, val);
    for (int i = newsize; i < sz; ++i)
        alloc.destroy(elem + i);

    sz = newsize;
}

template <typename T, typename A>
void vector<T, A>::push_back(const T &val)
{
    if (space == 0)
        reserve(8);
    else
    {
        if (sz == space)
        {
            reserve(2 * space);
        }
    }
    alloc.construct(elem + sz, val);
    ++sz;
};

#endif