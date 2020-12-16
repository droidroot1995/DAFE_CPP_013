#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include <iostream>
#include <memory>

template <typename T, typename A>
struct vector_base
{
    A alloc;
    T* elem;
    int sz;
    int space;
    vector_base(): elem{0}, sz{0}, space{0} {}
    vector_base (const A& a, int n)
        :alloc{a}, elem {alloc.allocate(n)}, sz{n}, space{n}{}
    ~vector_base()
    {
        alloc.deallocate (elem, space);
    }

};

#endif // VECTOR_BASE_H
