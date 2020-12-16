#include <iostream>
#include "vectorChapter18.h"

using namespace std;



int main()
{
    int n = 5;
    vector v2(n);
    for (int i = 0; i <n; ++i)
        v2[i] = i+1;
    for (int i = 0; i <n; ++i)
        cout << v2[i] << " ";
    return 0;
}
