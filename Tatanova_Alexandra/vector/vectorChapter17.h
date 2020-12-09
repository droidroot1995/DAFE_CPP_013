#ifndef VECTORCHAPTER17_H
#define VECTORCHAPTER17_H

class vector
{

  int sz; // Размер
  double* elem; // Указатель на элементы
public:
  vector (int s);
  ~vector () { delete [] elem; }
  int size() const { return sz; } // Текущий размер
  double get ( int n ) const {return elem[n];} // Чтение
  void set (int n, double v) {elem[n] = v;} // Запись
};

#endif // VECTORCHAPTER17_H
