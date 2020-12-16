#ifndef VECTOR_H
#define VECTOR_H

// Chapter 17 version
//
// In this version we can create vector of a certain size, get
// size value of object, store elements of double type, access them
// change their value and also this version has a destructor that
// deletes elements.

class vector
{
    int length;
    double* elements;
public:
    vector(int size);
    int size() const;
    ~vector();

    double get(int index) const;
    void set(int index, double value);
};

#endif // VECTOR_H
