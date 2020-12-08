// Vector2(18).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
using namespace std;
#include "vector2.h"

void ff(const vector& cv, vector& v)
{
    double d=cv[1];
    double x=v[1];
    v[1]=2.0;
}

int main()
{
    vector v1 = { 1,2,3 }; // Три элемента 1.0 , 2 . 0, 3 . 0
    vector v2(3); //// Три элемента со зна чениями по умолчанию (0. 0)
    vector v3{v1}; //Копирующее присваивание
    v3=v1;
    cout << v3.get(1) << endl;
    cout << v1.get(1) << endl;
    //vector v4{v2};
    v3.set(1,45);
    v1.set(1,60);
    cout << v1.get(1) << endl;
    cout << v3.get(1) << endl;

    vector v(10);
    for (int i=0; i<v.size(); i++)
    {
        v[i]=i;  //v[i] возвращает ссылку на i-й элемент
        cout<<v[i];
    }
    return 0;
}
