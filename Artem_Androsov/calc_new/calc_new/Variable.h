#pragma once							//
#include "Grammar.h"					// Подключение файла с объявлениями функций.


class Variable							// Класс Variable - объекты этого класса будут предствалять собой переменные.
{										// 
public:									//
	string name;						// Название переменной.
	double value;						// Значение переменной.
	bool cst;							// Является ли переменная константой.
};										//
		

extern vector<Variable> var_table;		// Вектор, в котором будут храниться все переменные.

double get_value(string s);				// Функция для получения значения переменной по её имени.
void set_value(string s, double d);		// Функция для изменения значения переменной (если она не константа).