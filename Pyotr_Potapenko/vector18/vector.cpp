#include "vector.h"
#include "algorithm"

vector::vector(int length)
    : length{length},
      elements{new double[length]}
{
    for (int i = 0; i < length; ++i)
        elements[i] = 0;
}

vector::vector(std::initializer_list<double> list)
    : length{static_cast<int>(list.size())},
      elements{new double[this->length]}
{
    std::copy(list.begin(), list.end(), elements);
}

vector::vector(const vector& arg)
    : length{arg.length},
      elements{new double[arg.length]}
{
    std::copy(arg.elements, arg.elements + length, elements);
}

vector::vector(vector&& vec)
    : length{vec.length},
      elements{vec.elements}
{
    vec.length = 0;
    vec.elements = nullptr;
}

vector& vector::operator=(vector&& vec) {
    delete []  elements;
    elements = vec.elements;
    length = vec.length;
    vec.elements = nullptr;
    vec.length = 0;
    return *this;
}

vector& vector::operator=(const vector& vec) {
    double* pointer = new double[vec.length];
    std::copy(vec.elements, vec.elements + vec.length, pointer);
    delete [] elements;
    elements = pointer;
    length = vec.length;
    return *this;
}

double* vector::operator[](int index){
    return &elements[index];
}

int vector::size() const {
    return length;
}

vector::~vector()
    { delete [] elements; }

double vector::get(int index) const {
    return elements[index];
}

void vector::set(int index, double value) {
    elements[index] = value;
}

