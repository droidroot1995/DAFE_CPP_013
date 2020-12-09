//
// Created by Алексей Ячменьков.
//

#ifndef VECTOR_VECC_H
#define VECTOR_VECC_H
#include <initializer_list>
#include <algorithm>
#include <memory>
#include <iostream>
struct Out_range: std::out_of_range
{
    int index;
    Out_range(int i):
    std::out_of_range("ERROR: Out of range!"), index{i} {};
};
template<typename T, typename A = std::allocator<T>> class vector
{
private:
    A alloc; //Распределитель памяти
    int sz; // Количество элементов
    T* elem; //Начало выделенной памяти
    int space; //Размер выделенной памяти
    void reserve(int);
public:
    vector();
    explicit vector(int);
    vector(std::initializer_list<T>);
    vector(const vector&); //Копирующий конструктор
    vector(vector&&);

    T& at(int);

    vector& operator=(vector&&);
    vector& operator=(const vector&);
    T& operator[](int);
    T operator[](int) const;

    int size() const; // Текущий размер
    T get(int) const;
    void set(int, T);
    void resize(int, T val=T());
    void push_back(const T&);
    int capacity() const;
    ~vector();
};
#endif //VECTOR_VECC_H
