//
//  allocations.cpp
//  Vector_1.0
//
//  Created by Bogdan Bochkarev on 12/10/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "allocations.hpp"

template<typename T>
T* allocator<T>::allocate(int n)
{
    // c
    //return static_cast<T*>(malloc(sizeof (T) * n));

    // c++
    return reinterpret_cast<T*>(new char[sizeof(T) * n]);
}


template<typename T>
void allocator<T>::deallocate(T *p, int n) {
    // c
    // free(p);

    // c++
    delete[] reinterpret_cast<T*>(p);
}


template<typename T>
void allocator<T>::construct(T *p, const T &v) {
    // c++
    new(p) T(v);
}

template<typename T>
void allocator<T>::destroy(T *p) {
    // c++
    p->~T();
}
