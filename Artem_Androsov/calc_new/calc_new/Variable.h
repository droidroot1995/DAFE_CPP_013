#pragma once
#include "funcs.h"

class Variable
{
public:
	string name;
	double value;
	bool cst;
};

extern vector<Variable> var_table;

double get_value(string s);
void set_value(string s, double d);