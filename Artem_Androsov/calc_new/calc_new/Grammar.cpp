#include "Variable.h"

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0)
			{
				error("Deviding by zero");
			}
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0)
			{
				error("%: deviding by zero");
			}
			left = i1 % i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			error("')' is needed");
		}
		return d;
	}
	case '@':
	{
		double d = primary();
		if (d < 0)
		{
			error("sqrt: a negative number");
		}
		return sqrt(d);
	}
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case '-':
		return -primary();
	case '+':
		return primary();
	default:
		error("expression is needed");
	}
}
