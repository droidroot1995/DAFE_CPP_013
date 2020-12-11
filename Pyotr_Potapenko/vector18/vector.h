#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>

class vector
{
    int length;
    double* elements;
public:
    vector(int size);
    vector(std::initializer_list<double> list);
    vector(const vector& vec);
    vector(vector&& vec);

    vector& operator=(const vector& vec);
    vector& operator=(vector&& vec);
    double* operator[](int index);

    int size() const;

    double get(int index) const;
    void set(int index, double value);

    ~vector();
};
#endif // VECTOR_H
