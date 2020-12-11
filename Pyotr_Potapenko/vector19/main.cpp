#include <iostream>

#include "vector.h"
#include "vector.cpp"

int main()
{
    vector_<double> v{ 1, 2, 3 };
    vector_<int> vec {1, 0, 1};

    vec.push_back(2);

    std::cout << vec[3] << std::endl;

    return 0;
}
