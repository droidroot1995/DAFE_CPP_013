#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
using namespace std;

class vector
{
    int sz;          // The size
    double* elem;    // Pointer to the first element (of type double)
public:
    vector(int s) :           //Constructor
        sz{ s },              // sz member initialization
        elem{ new double[sz] }   // Elem member initialization
    {
        for (int i = 0; i < sz; i++)  // initialization
            elem[i] = 0.0;            // elements
    }

    vector(vector&& a);          // Moving constructor
    vector& operator=(vector&&); // Relocation assignment
    vector(const vector&);       // Copy constructor

    double &operator[](int n) // For non-const vectors
    {
        return elem[n];
    }

    double &operator[](int n) const // for constant vectors
    {
        return elem[n];
    }

    vector& operator=(const vector&); // Copy assignment
    // Constructor with initialization list
    // needed to initialize the list so that
    // you don't need to initialize each separately
    vector(initializer_list<double> lst)
    {
        sz= lst.size();
        elem=new double[sz]; // Uninitialized memory
        // Initialization with std :: copy ();
        copy(lst.begin(), lst.end(), elem); // due to this we make vector v1 = {1,2,3};
        /* He (copy)
        copies the sequence of elements defined by the first two
        arguments (in this case, the start and end of the initializer_list)
        into a sequence of elements whose beginning indicates
        its third argument (in this case, the sequence
        vector elements, starting with elem). */
    }


    ~vector()           // Destructor, free memory
    {
        delete[] elem;
    }
    // Constructor: allocates s numbers in memory
    // of type double, points to them pointer
    // elem and stores s into sz

    int size() const { return sz; } //Current size
    double get(int n) const { return elem[n]; } //Reading
    void set(int n, double v) { elem[n] = v; } //Writing
};

#endif // VECTOR2_H
