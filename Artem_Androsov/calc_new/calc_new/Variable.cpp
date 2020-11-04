#include "Variable.h"

double get_value(string s)
{
	for (const Variable& v : var_table)
	{
		if (v.name == s)
		{
			return v.value;
		}
	}
	error("get: undefined variable ", s);
}

void set_value(string s, double d)
{
	for (Variable& v : var_table)
	{
		if (v.name == s)
		{
			if (v.cst)
			{
				error("can not change value of a const");
			}
			v.value = d;
			return;
		}
	}
	error("set: undefined variable ", s);
}