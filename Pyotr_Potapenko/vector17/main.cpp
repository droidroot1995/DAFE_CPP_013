#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
    vector v = vector(10);
    v.set(1, 7);

    cout << "Value of the second element: " << v.get(1) << '\n' <<
            "Value of the third element: " << v.get(2) << '\n' <<
            "Vector's size: " << v.size()  << '\n';
    return 0;
}
