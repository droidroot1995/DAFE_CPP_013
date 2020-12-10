#include <iostream>
#include "vectorChapter19.h"
using namespace std;






template<class T>
void print(const vector<T>& vec){
    for (int i = 0; i < vec.size(); ++i)
        cout << " _"<< vec[i] << "_ ";
    cout << "\n";
}

string str(int n){
    return string(1, '0' + n);
}

int main()
{
    int n = 5;
    vector<string> v(n);
    print(v);
    for (int i = 0; i < v.size(); ++i){
        v[i] = str(i);
    }
    print(v);
    for (int i = 0; i < 15; ++i){
        v.push_back(str(i));
    }
    print(v);
    vector <int> d(5);
    for (int i = 0; i < 5; ++i)
        d[i] = i + 1;
    print(d);
    for (int i = 0; i < 3; ++i)
        d.push_back(i);
    print(d);

    cout << " Size d: " << d.size() << endl;
    d.resize(10);
    cout << " Size d: " << d.size() << endl;
    return 0;
}



