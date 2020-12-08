#include "vector2.h"



vector::vector(vector&& a)
    :sz{a.sz}, elem{a.elem} // Копируем elem и sz из а
{
    a.sz=0;         //Делаем вектор а пустым
    a.elem=nullptr;
}

vector& vector::operator=(const vector& a)
{
    double*p=new double[a.sz];   //Выделение памяти
    copy(a.elem, a.elem+a.sz,p); //Копирование элементов
    delete[] elem;               //Освобождение памяти
    elem=p;                      //Переназначение указателя
    sz=a.sz;
    return *this; //Возврат ссылки на себя
}

vector::vector(const vector& arg)
    :sz{arg.sz}, elem{new double[arg.sz]} //Размещает элементы, инициализирует их копированием
{
    for (int i = 0; i < sz; i++)
    {
        this->elem[i] = arg.elem[i];
    }
}

vector& vector::operator=(vector&& a) //Перемещаем а в текущий вектор
{
    delete[] elem;// Освобождение старой памяти
    elem=a.elem;  // Копирование elem и sz из а
    sz=a.sz;
    a.elem=nullptr;  //делаем вектор пустым
    a.sz=0;
    return *this;   //Возврат ссылки на себя
}

