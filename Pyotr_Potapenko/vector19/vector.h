#ifndef VECTOR_H
#define VECTOR_H
#include <algorithm>
#include <iostream>
#include <memory>

template<typename T, typename A>struct vector_base
{
    A allocator;
    T* elements;
    int length;
    int space;

    vector_base(){};
    vector_base(A& a, int n):
        allocator{a}, elements{a.allocate(n)}, length{n}, space{n}{}
    ~vector_base() {allocator.deallocate(elements,space);}
};

template<typename T, typename A=std::allocator<T>> class vector_:private vector_base<T,A>
{
    A allocator;
    int length;
    T* elements;
    int space;
public:

    vector_():length{0}, elements{nullptr}, space{0} {}
    explicit vector_(int s): length{s}, elements{new T[s]}, space{s}
    {
        for (int i=0; i<length; i++)
            elements[i]=0;
    }

    vector_(const vector_& a);
    vector_& operator=(const vector_& a);

    vector_(vector_&& a);
    vector_& operator=(vector_&&);
    ~vector_()  {delete[] elements;}

    T& at(int n);
    const T& at(int n) const;

    T &operator[](int n);
    const T& operator[](int n) const { return elements[n]; }


    vector_(const std::initializer_list<T>& lst);
    int size() const { return length; }
    int capacity() const;

    void reserve(int newalloc);
    void resize(int newsize, T val=T());
    void push_back(const T& val);

    T get(int n) const { return elements[n]; }
    void set(int n, T v) { elements[n] = v; }
};



#endif // VECTOR_H
