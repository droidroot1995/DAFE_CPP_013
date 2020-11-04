#include "Grammar2.h"

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	case set:
		return sett();
	default:
		ts.putback(t);
		return expression();
	}
}

bool is_declared(string var)
{
	for (const Variable& v : var_table)
	{
		if (v.name == var)
		{
			return true;
		}
	}
	return false;
}

double define_name(string var, double val, bool c)
{
	if (is_declared(var))
	{
		error(var, " second defining");
	}
	var_table.push_back(Variable{ var, val, c });
	return val;
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name)
	{
		error("variable name is missing");
	}
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=')
	{
		error("'=' is missing in declaration of ", var_name);
	}

	double d = expression();
	define_name(var_name, d, false);
	return d;
}

double sett()
{
	Token t = ts.get();
	if (t.kind != name)
	{
		error("variable name is missing");
	}
	string var_name = t.name;

	if (!is_declared(var_name))
	{
		error("variable does not exist");
	}

	Token t2 = ts.get();
	if (t2.kind != '=')
	{
		error("'=' is missing in setting ", var_name);
	}

	double d = expression();
	set_value(var_name, d);
	return d;
}