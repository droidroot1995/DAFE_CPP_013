#ifndef VECTORCHAPTER19_H
#define VECTORCHAPTER19_H

#include <iostream>
#include <memory>
#include <string>
#include "vector_base.h"

template <typename T, typename A = std::allocator <T>>
class vector: private vector_base<T, A>
{
    void set_sz(int sz_) {sz = sz_;}
  A alloc;
  int sz; // Размер
  T* elem; // Указатель на элементы
  int space; // Количество элементов плюс своюодное место(слоты)
            // для новых элементов(текущий выделенный размер)
  void copy(const vector& arg);
public:

  vector(): sz{0}, elem{nullptr}, space{0} {}
  explicit vector (int s) :sz{s}, elem{alloc.allocate(s)}, space{s}
  {
      for (int i = 0; i < sz; ++i)
//          elem[i] = T(); //Элементы иницилиазированы
          alloc.construct(elem+i, T());
  }
  vector (const vector&); // Копирующий конструктор
  vector& operator= (const vector& ); // Копирующее присваивание

  ~vector ()  // Деструктор
  {
      for(int i = 0; i < sz; ++i){
          alloc.destroy(elem + i);
      }
      alloc.deallocate(elem, sz);
  }

  T& at(int n);
  const T& at (int n) const;
  T& operator[](int n){return elem[n]; } // Доступ без проверки
  const T& operator[](int n) const{return elem[n]; };

  int size() const { return sz; } // Текущий размер
  int capacity() const { return space; }

  void resize (int newsize, T val = T()); // Увеличение
  void push_back ( const T& d);
  void reserve (int newalloc);

};

template<class T, class A>
vector<T,A>::vector(const vector& arg)
    :sz{arg.sz}, space{arg.sz}, elem{alloc.allocate(arg.space)}
{
    copy(arg);
}

template<class T, class A>
vector<T,A>& vector<T,A> :: operator= (const vector& a) // Делаем данный вектор копией а
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
    T* p = alloc.allocate(a.space);
    for(int i=0; i<a.sz; i++)
        alloc.construct(&p[i],a.elem[i]);
    for(int i=0; i<sz; i++)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem,space);
    space = sz = a.sz;
    elem = p; // Переназначение указателя
    return *this; // Возрат ссылки на себя

}
template<class T, class A>
void vector<T,A>::copy(const vector& arg) {
    for(int i=0; i<arg.sz; i++)
        alloc.construct(elem+i,arg[i]);
}
template <typename T, typename A>
T& vector <T, A> :: at(int n)
{
   if (n<0 || sz <= n)
   {
      std::string  s = "Wrong index";
       throw std::out_of_range(s);
   }
   return elem[n];
}
template <typename T, typename A>
const T& vector <T, A> :: at(int n) const
{
   if (n<0 || sz <= n)
   {
      std::string  s = "Wrong index";
       throw std::out_of_range(s);
   }
   return elem[n];
}

//struct Range_errow: out_of_range
//{
//    int index;
//    Range_errow(int i): out_of_range(" Range error "), index{i} {}
//};


template <typename T, typename A>
void vector <T, A> :: reserve (int newalloc)
{
    if (newalloc<=this->space)
        return;// Размер не уменьшается
    vector_base<T,A> b(this->alloc, newalloc);
//    uninitialized_copy (b.elem, &b.elem[this->sz],this->elem) ;// Копирование
    uninitialized_copy (elem, elem + sz, b.elem) ;// Копирование
    for (int i=0; i<this->sz; ++i)
        this->alloc.destroy ( &this->elem[i] );
    std::swap<vector_base<T,A>> (*this, b);
}


template <typename T, typename A>
void vector<T, A> :: resize (int newsize, T val ) //
{
    reserve (newsize);
    for (int i = sz; i < newsize; ++i)
        alloc.construct(elem + i, val); // Создаем
    for (int i = newsize; i < sz; ++i)
        alloc.destroy(elem + i); // Уничтожаем

    sz = newsize;
}


template <typename T, typename A>
void vector<T, A>::push_back( const T& val) //
{
    if (space == 0)
        reserve(8);
    else{
        if (sz == space){
            reserve (2*space);
        }
    }
    alloc.construct(elem + sz, val);/*
    cout<< "_" << sz << " "<<space;
    elem[sz] = val;*/
    ++sz;
};

#endif // VECTORCHAPTER19_H
