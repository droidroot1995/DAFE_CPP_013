// Vector3(19).cpp
//760

#include "vector3.h"
#include "vector3.cpp"
#include <string>


void print_some(vector<int>& v)
{
    int i=-1;
    while (cin>>i && i!=-1)
        try
    {
        cout<<"v["<<i<<"]=="<<v.at(i)<<"\n";

    }
    catch (out_of_range)
    {
        cout<<"Неверный индекс: "<<i<<"\n";
    }
}

int main()
{
    vector<double> v1  { 1,2,3 }; // Три элемента 1.0 , 2 . 0, 3 . 0
    vector<double> v2(3); // Три элемента со зна чениями по умолчанию (0. 0)
    vector<double> v3{v1}; // Копирующее присваивание
    v3=v1;
    cout << v3.get(1) << endl;
    cout << v1.get(1) << endl;
    //vector v4{v2};
    v3.set(1,45);
    v1.set(1,60);
    cout << v1.get(1) << endl;
    cout << v3.get(1) << endl;

    cout<<v2.capacity();
    vector<int> v(10);
    for (int i=0; i<v.size(); i++)
    {
        v[i]=i;  //v[i] возвращает ссылку на i-й элемент
        cout<<v[i];
    }
    cout<<endl<<v2.capacity();
    v2=v1;
    v2.reserve(7);
    cout<<endl<<v2.capacity();
    cout<<v2[0]<<endl<<v2[1]<<endl<<v2[2]<<endl<<v2[4]<<endl;
    v2.resize(10);
    for (int i=0; i<v2.size(); i++)
        cout<<v2[i];
    cout<<v.get(4);
    vector<char> vchar{'h'};
    //string s="dsfa";
    //cout<<s;
    vector<string> vstr{"gdfghsj"};
    cout<<vstr.get(0);
    v.resize(3);
    return 0;
}
