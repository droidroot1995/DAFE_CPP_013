#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
using namespace std;

class vector
{
    int sz;          //Размер
    double* elem;    // Указатель на первый элемент (типа double)
public:
    vector(int s) :           //Конструктор
        sz{ s },              // Инициализация члена sz
        elem{ new double[sz] }   // Инициализация члена elem
    {
        for (int i = 0; i < sz; i++)  // инициализация
            elem[i] = 0.0;            // элементов
    }

    vector(vector&& a);          //Перемещающий конструктор
    vector& operator=(vector&&); //Перемещающее присваивание
    vector(const vector&); //Конструктор копирования

    double &operator[](int n) //Для неконстантных векторов
    {
        return elem[n];
    }

    double operator[](int n) const //для константных векторов
    {
        return elem[n];
    }

    vector& operator=(const vector&); //Копирующее присваивание
    //Конструктор со списком инициализации
    vector(initializer_list<double> lst)
    {
        sz= lst.size();
        elem=new double[sz]; //Неинициализированная память
        // Инициализация с помощью std::copy ();
        copy(lst.begin(), lst.end(), elem); //за счёт этого делаем vector v1 = { 1,2,3 };
        /*Он (copy)
копирует последовательность элементов, определяемую первыми двумя
аргументами (в данном случае - начало и конец initiali zer_list)
в последовательность элементов, начало которой указывает
его третий аргумент (в данном случае - последовательность
элементов вектора, начинающаяся с elem). */
    }


    ~vector()           //Деструктор, освобождает память
    {
        delete[] elem;
    }
    // Конструктор: размещаает в памяти s чисел
    // типа double, направляет на них указатель
    // elem и сохраняет s в член sz

    int size() const { return sz; } //Текущий размер
    double get(int n) const { return elem[n]; } //Чтение
    void set(int n, double v) { elem[n] = v; } //Запись
};

#endif // VECTOR2_H
