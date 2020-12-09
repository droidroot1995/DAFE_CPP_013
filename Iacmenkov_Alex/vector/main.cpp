#include <iostream>
#include "vecc.h"
int main()
{
    vector<int> v(6);
    v[0] = 12;
    v[1] = 2;
    v.push_back(10);
    for(int i = 3; i <7;++i)
        v.push_back(i);
    for (int i=0; i<v.size(); ++i)
        std::cout << "v[" << i << "]=" << v.get(i) << std::endl;
    vector<double> v1(5) ;
    for (int i=0; i<v1.size(); ++i)
    {
        v1.set(i,1.2*i);
        std::cout << "v1[" << i << "]=" << v1.get(i) << std::endl;
    }
    vector<double> v2 = {5.0};
    for (int i=0; i<v2.size(); ++i)
        std::cout << "v2[" << i << "]=" << v2.get(i) << std::endl;
    vector<double> v3 = v2;
    std::cout << v3.get(0) << std::endl;
    v3.set(0, 4.0);
    v3.push_back(6.7);
    for (int i=0; i<v3.size(); ++i)
        v3.set(i,2.1*i);
    for (int i=0; i<v3.size(); ++i)
        std::cout << "v3[" << i << "]=" << v3.get(i) << std::endl;
    vector<char> v4(6);
    v4[0] = 'A';
    v4.set(5, 'B');
    for (int i=0; i<v4.size(); ++i)
        std::cout << "v4[" << i << "]=" << v4[i] << std::endl;
    vector<std::string> v5(6);
    v5[3] = "BARLY";
    for (int i=0; i<v5.size(); ++i)
        std::cout << "v5[" << i << "]=" << v5[i] << std::endl;
    return 0;
}