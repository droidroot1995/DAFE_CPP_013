//Ysupov Safuan 17.10.20  
/*
������� �����������

������� ������:

������������ �������� �������� � ������� 2020 (09.10.20)
����������� ������ ������������ � ��� 2007 �.
����������� ������ ������������ � ������� 2006 �.
����������� ������ ������������ � ������� 2004 �.
���������� ������ ������������ (bs@cs.tamu.edu) ������ 2004 �.

��� ��������� ��������� �������� ��������� ������������.
���� �������������� �� ������ cin ; ����� - � ����� cou t.

������ ���� ��� ����� :

����������:
  ���������
  �����
  �����

�����:
    ;
�����:
    q

���������:
  ����
  ��������� + ����
  ��������� - ����

����:
  ���������_���������
  ���� * ���������_���������
  ���� / ���������_���������
  ���� % ���������_ ���������

���������_��������� :
  �����
  ( ��������� )
  - ���������_���������
  + ���������_���������

����� :
  �������_�_���������_������

���� �� ������ cin ����� Token stream � ������ ts.
*/
#include "std_lib_facilities.h"
#include <iostream>
#include "Variable.h"
#include "Functions.h"
using namespace std;

int main()
try
{
    cout << "use 'help'"<<endl<<endl;
    setlocale(LC_ALL, "Russian");
    //Predefined names
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);
    define_name("k", 1000);

    calculate();

    //keep_window_open(); // Keeps the console window open
    return 0;
}
catch (runtime_error& e)   //exception
{
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}

catch (...)
{
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}