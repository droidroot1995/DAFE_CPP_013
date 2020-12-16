#include "vector2.h"
//Realisation

vector::vector(vector&& a)
    :sz{a.sz}, elem{a.elem} // Copy elem and sz from a
{
    a.sz=0;         //Делаем вектор а пустым
    a.elem=nullptr;
}

vector& vector::operator=(const vector& a)
{
    double*p=new double[a.sz];    // Memory allocation
    copy(a.elem, a.elem+a.sz, p); // Copy items
    delete[] elem;                // Free memory
    elem=p;                       // Reassign the pointer
    sz=a.sz;
    return *this;                 // Return a link to itself
}

vector::vector(const vector& arg)
    :sz{arg.sz}, elem{new double[arg.sz]} // Places elements, initialize them by copying
{
    for (int i = 0; i < sz; i++)
    {
        this->elem[i] = arg.elem[i];
    }
}

vector& vector::operator=(vector&& a) // Places elements, initialize them by copying
{
    delete[] elem;   // Free old memory
    elem=a.elem;     // Копирование elem и sz из а
    sz=a.sz;
    a.elem=nullptr;  // make the vector empty
    a.sz=0;
    return *this;    // Returning a link to yourself
}

