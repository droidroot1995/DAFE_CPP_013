//
//  logic.cpp
//  Vector_1.0
//
//  Created by Bogdan Bochkarev on 11/11/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "logic.hpp"


//constructors
//----------------------------------
template<typename T, typename A>
Vector<T, A>::
Vector(): sz{0}, elem{nullptr}, space{0} {} // das ergibt noch keinen Sinn, aber wir lassen das bis dann


template<typename T, typename A>
Vector<T, A>::
Vector(int s): sz{s}, elem{new T[sz]}, space{sz} {
    for (int i=0; i<s; ++i) elem[i] = T();
}


template<typename T, typename A>
Vector<T, A>::
Vector(std::initializer_list<T> lst):
sz{static_cast<int>(lst.size())}, elem{new T[sz]}, space{sz} {
    std::copy(lst.begin(), lst.end(), elem);
}


template<typename T, typename A>
Vector<T, A>::
Vector(const Vector<T, A>& arg): sz{arg.sz}, elem{new T[arg.sz]}, space{sz} {
    std::copy(arg.elem, arg.elem+sz, elem);
}


template<typename T, typename A>
Vector<T, A>::
Vector(Vector<T, A>&& a): sz{a.sz}, elem{a.elem}, space{sz} {
    a.sz = 0; a.elem = nullptr; a.space = a.sz;
}


//memory organization
//----------------------------------
template<typename T, typename A>
void Vector<T, A>::
reserve(int newalloc) {
    if (newalloc <= space) return;
    T* p = alloc.allocate(newalloc);
    for (int i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);
    for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
    elem = p;
    space = newalloc;
}


//element access function
//----------------------------------
template<typename T, typename A>
T& Vector<T, A>::
at(int n) {
    if (0 <= n && n <= sz) return elem[n];
    throw Range_error(n);
}


//operators
//----------------------------------
template<typename T, typename A>
Vector<T, A>& Vector<T, A>::
operator=(Vector<T, A>&& a) {
    delete[] elem;
    elem = a.elem; sz = a.sz;
    a.sz = 0; a.elem = nullptr;
    return *this;
}


template<typename T, typename A>
Vector<T, A>& Vector<T, A>::
operator=(const Vector<T, A>& a) {
    if (&a == this) return *this;
    if (a.sz <= space) {
        for (int i = 0; i<a.sz; ++i) elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }
    T* p = new T[a.sz];
    for (int i = 0; i<a.sz; ++i) p[i] = a.elem[i];
    delete[] elem; elem = p; space = sz = a.sz;
    return *this;
}


template<typename T, typename A>
T& Vector<T, A>::
operator[](int n) {
    return at(n);
}


template<typename T, typename A>
T Vector<T, A>::
operator[](int n) const {
    if (0 <= n && n <= sz) return elem[n];
    throw Range_error(n);
}


//functions for users
//----------------------------------
template<typename T, typename A>
int Vector<T, A>::
size() const {
    return sz;
}


template<typename T, typename A>
T Vector<T, A>::
get(int n) const {
    return elem[n];
}


template<typename T, typename A>
void Vector<T, A>::
set(int n, T t) {
    elem[n]=t;
}


template<typename T, typename A>
void Vector<T, A>::
resize(int newsize, T val) {
    reserve(newsize);
    for (int i=sz; i<newsize; ++i) alloc.construct(&elem[i], val);
    for (int i=sz; i<newsize; ++i) alloc.destroy(&elem[i]);
    sz = newsize;
}


template<typename T, typename A>
void Vector<T, A>::
push_back(const T& val) {
    if (!space) reserve(8);
    else if (sz == space) reserve(2*space);
    alloc.construct(&elem[sz], val);
    ++sz;
}


template<typename T, typename A>
int Vector<T, A>::
capacity() const {
    return space;
}


//destructor
//----------------------------------
template<typename T, typename A>
Vector<T, A>::
~Vector() {
    delete[] elem;
}


//templates declaration
//----------------------------------
template class Vector<double>;
template class Vector<int>;
template class Vector<char>;
template class Vector<std::string>;
