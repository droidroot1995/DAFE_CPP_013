// Vector3(19).cpp
//760

#include "vector3.h"
#include "vector3.cpp"
#include <string>


template<typename T>
void print(const Vector<T>& v)
{
    cout<<v.size()<<endl;
    for(size_t i = 0; i < v.size(); ++i)
        cout<<v[i]<<" ";
    cout<<endl;
}

Vector<string> make_vec()
{
    Vector<string> res{"car", "bus"};
    cout<<res[0];
    //заполнение вектора
    res.push_back("plane");
    res.push_back("ship");
    print(res);
    return res;
}

int main()
{
    Vector<double> v1  { 1,2,3 }; // Три элемента 1.0 , 2 . 0, 3 . 0
    Vector<double> v3{3.0, 2.1, 10, 4, 5, 6, 1, 1, 1, 1, 1};
    Vector<double> v5(10);
    Vector<double> v7{3.0, 2.1, 10, 4, 4, 4, 4, 12, 1};
    v1.push_back(4.3);
    v1.push_back(3.2);
    v1.push_back(10.0);
    v1[2] = 4;
    cout<<"v1 "<<endl;
    print(v1);
    v1 = v3;
    print(v1);
    cout << endl;
    cout<<endl;

    Vector<int> v11{1,4,5};
    cout<<v11[1]<<endl;

    Vector<string> vol(10);
    Vector<string> vs{"fasfas", "fsds"};

    cout<<vs[0]<<endl;
    vol = make_vec();
    print(vol);
    return 0;
}
