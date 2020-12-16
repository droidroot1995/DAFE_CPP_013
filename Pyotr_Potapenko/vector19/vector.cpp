#include "vector.h"

struct Range_error: std::out_of_range {
  int index;
  Range_error(int i): out_of_range {
    "Range error"
  }, index {
    i
  } {}
};

template < typename T > struct Vector: public vector_ < T > {
  using size_type = typename vector_ < T > ::size_type;
  using vector_ < T > ::vector;

  T & operator[](size_type i) {
    if (i < 0 || this -> size() <= i)
      throw Range_error(i);
    return vector_ < T > ::operator[](i);
  }

  const T & operator[](size_type i) const {
    if (i < 0 || this -> size() <= i)
      throw Range_error(i);
    return vector_ < T > ::operator[](i);
  }
};

template < typename T, typename A > vector_ < T, A > ::vector_(const std::initializer_list < T > & lst):
  length {
    int(lst.size())
  },
  elements {
    new T[length]
  } {

    std::copy(lst.begin(), lst.end(), elements);

  }

template < typename T, typename A > vector_ < T, A > & vector_ < T, A > ::operator = (const vector_ < T, A > & a) {
  if (this == & a) return *this;

  if (a.length <= space) {
    for (int i = 0; i < a.length; i++)
      elements[i] = a.elements[i];
    length = a.length;
    return *this;
  }
  T * p = new T[a.length];
  for (int i = 0; i < a.length; i++)
    p[i] = a.elements[i];
  delete[] elements;
  space = length = a.length;
  elements = p;
  return *this;
}

template < typename T, typename A > vector_ < T, A > ::vector_(vector_ < T, A > && a): length {
  a.length
}, elements {
  a.elements
} {
  a.length = 0;
  a.elements = nullptr;
}

template < typename T, typename A > vector_ < T, A > ::vector_(const vector_ < T, A > & arg): length {
  arg.length
}, elements {
  new T[arg.length]
} {
  copy(arg.elements, arg.elements + arg.length, elements);
}

template < typename T, typename A > vector_ < T, A > & vector_ < T, A > ::operator = (vector_ < T, A > && a) //Перемещаем а в текущий вектор
{
  delete[] elements;
  elements = a.elements;
  length = a.length;
  a.elements = nullptr;
  a.length = 0;
  return *this;
}

template < typename T, typename A > int vector_ < T, A > ::capacity() const {
  return space;
}

template < typename T, typename A > void vector_ < T, A > ::reserve(int newalloc) {
  if (newalloc <= this -> space) return;
  vector_base < T, A >
    b(this -> allocator, newalloc);
  std::uninitialized_copy(b.elements, & b.elements[this -> length], this -> elements);
  for (int i = 0; i < this -> length; i++)
    this -> allocator.destroy( & this -> elements[i]);
  std::swap < vector_base < T, A >> ( * this, b);
}

template < typename T, typename A > void vector_ < T, A > ::resize(int newsize, T val) {
  reserve(newsize);
  for (int i = length; i < newsize; i++)
    allocator.construct( & elements[i], val);
  for (int i = newsize; i < length; i++)
    allocator.destroy( & elements[i]);
  length = newsize;
}

template < typename T, typename A > void vector_ < T, A > ::push_back(const T & val) {
  if (space == 0)
    reserve(8);
  else if (length == space)
    reserve(2 * space);
  allocator.construct( & elements[length], val);
  ++length;
}

template < typename T, typename A > T & vector_ < T, A > ::at(int n) {
  if (n < 0 || length <= n)
    throw std::out_of_range("");
  return elements[n];
}

template < typename T, typename A > T & vector_ < T, A > ::operator[](int n) {
  return elements[n];
}
