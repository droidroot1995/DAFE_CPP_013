#pragma once
#include "Variable.h"									// ����������� ����� ��� ������ � �� ����� ������������ �������� � ���������.

void calculate();
double statement();										// ������� ��� ��������� �������� ������������������ ��������.
double declaration();									// ������� ��� �������� ����� ����������
double sett();											// �������, ���������� �������� ����������.

bool is_declared(string var);							// ������� �����������, ���������� �� ��� ����� ����������.
double define_name(string var, double val, bool c);		// �������, ������������ ����������� ����������.

