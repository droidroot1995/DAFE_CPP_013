#include "vector.h"

vector::vector(int length)
    : length{length},
      elements{new double[length]}
{
    for (int i = 0; i < length; ++i)
        elements[i] = 0;
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
