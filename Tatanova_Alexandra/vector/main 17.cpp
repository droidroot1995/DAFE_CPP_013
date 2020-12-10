#include <iostream>
#include "vectorChapter17.h"
using namespace std;


int main()
{
    vector v(5);
    for (int i=0; i< v.size(); ++i)
    {
        v.set(i, 1.1*i) ;
        cout << "v [" << i << "]==" << v.get(i) << endl;
    }
    return 0;
}
