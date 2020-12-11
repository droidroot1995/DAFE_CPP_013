//
//  logic.hpp
//  Vector_1.0
//
//  Created by Bogdan Bochkarev on 11/11/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef logic_hpp
#define logic_hpp
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <initializer_list>
#include <algorithm>
#include <memory>
#include <string>


struct Range_error: std::out_of_range {
    int index;
    Range_error(int i): std::out_of_range("Range error"), index{i} {};
};


template<typename T, typename A>
struct vector_base {
    A alloc;    // memory allocator
    int sz;     // quantity of elements
    T* elem;    // pointer to the start of the allocated memory
    int space;  // size of allocated memory
    
    vector_base();
    vector_base(int);
    vector_base(const A&, int);
    vector_base(const vector_base&);
    vector_base(std::initializer_list<T>);
    vector_base(vector_base&&);
    ~vector_base();
};


template<typename T, typename A = std::allocator<T>>
class Vector : private vector_base<T, A> {
private:
    void reserve(int);

public:
    Vector();
    explicit Vector(int);
    Vector(std::initializer_list<T>);
    Vector(const Vector&);
    Vector(Vector&&);


    T& at(int);

    
    Vector& operator=(Vector&&);
    Vector& operator=(const Vector&);

    T& operator[](int);
    T operator[](int) const;


    int size() const; // Текущий размер
    T get(int) const;
    void set(int, T);
    void resize(int, T val=T());
    void push_back(const T&);
    int capacity() const;


    ~Vector();
};

#endif /* logic_hpp */
