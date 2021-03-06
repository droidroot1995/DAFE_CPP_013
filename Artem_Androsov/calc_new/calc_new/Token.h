#pragma once
#include <iostream>												// ����������� ����������� ����������, 
#include "std_lib_facilities.h"									// ���������� �� �������� �����������
#include "consts.h"												// � ����������� ��������.
using namespace std;


class Token														// ����� Token - ������� ����� ������ ����� ������������ ��������,
{																// �� ������� �� ����� ��������� �������� ���������.
public:
	char kind;													// ������������ ���� �������� (�����, ����).
	double value;												// �������� �������� (��� �������-�����).
	string name;												// ��� �������� (��� �������� ����).

	Token(char ch) :kind{ ch } { };								// ������������ ������ ��� �������� ��������� �������.
	Token(char ch, double val) :kind{ ch }, value{ val } { };	//
	Token(char ch, string n) :kind{ ch }, name{ n } { };		//
};



class Token_stream												// ����� Token_stream - ������ ����� ������ ����� ������� � ��������
{																// ������ ����� �������, ������� ����� ��������������� ������� ������ � �������������
public:															// ��������.
	Token get();												// ������� ��� ��������� ��������� �������� �� ������.
	void putback(Token t);										// ������� ��� �������� �������� ������� � �����.
	void ignore(char c);										// ������� ��� �������� ������� � ������ ������.
private:
	bool full{ false };											// ������ ����, ����� �� �����.
	Token buffer{'\0'};											// ����� ������, ������������ �������� putback(...).
};