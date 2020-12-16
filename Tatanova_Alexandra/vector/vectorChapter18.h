#ifndef VECTORCHAPTER18_H
#define VECTORCHAPTER18_H
#include <iostream>


#endif // VECTORCHAPTER18_H
class vector
{

  int sz; // Размер
  double* elem; // Указатель на элементы
  int space; //
public:
  vector();
  explicit vector(int s);
  vector (const vector& );  // Копирающее Конструктор
  vector& operator= (const vector& ); // Копирающее присваивание
  vector ( vector&& a ); // Перемещающий конструктор
  vector& operator=( vector&& ); // Перемещающее присваивание
  ~vector () { delete [] elem; }
  double& operator[](int n) { return elem[n]; }

  const double& operator[](int n) const { return elem[n]; }
  int size() const {return sz; }
  int capacity() const { return space; }

  void resize (int newsize);
  void push_back(double d);
  void reserve (int newalloc);

};
