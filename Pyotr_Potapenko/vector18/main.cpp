#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
    vector vec = {1, 2, 3, 4};
    vector not_a_vec = vec;
    vec.set(3, 1);
    cout << not_a_vec.get(3) << endl;
    return 0;
}
