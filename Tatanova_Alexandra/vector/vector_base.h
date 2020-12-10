#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include <iostream>
#include <memory>
#include "tracer.h"

template <typename T, typename A>
struct vector_base
{
    A alloc;
    T* elem;
    int sz;
    int space;
    vector_base(): elem{0}, sz{0}, space{0} {
        TRACE_FUNC;
    }
    vector_base (const A& a, int n)
        :alloc{a}, elem {alloc.allocate(n)}, sz{n}, space{n}{
        TRACE_FUNC;
    }
    ~vector_base()
    {
        TRACE_FUNC;
        alloc.deallocate (elem, space);
    }
//    vector_base(vector_base&& vec){

//    }

};

#endif // VECTOR_BASE_H
