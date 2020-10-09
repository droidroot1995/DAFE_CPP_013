#include <iostream>
#include "std_lib_facilities.h"
#include "TokenStr.h"
#include "Fun.h"

extern Token_stream ts;

double expression();

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
			error("'(' expected");
	}

	case '-':
		return -primary();
	case '+':
		return +primary();

	case number:
		return t.value;

	case name:
		return get_value(t.name);

	default:
		error("primary expected");
	}
}


double term()
{
	double left = primary();
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '*':
			left *= primary();
			break;

		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
}


double expression()
{
	double left = term();
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '+':
			left += term();
			break;

		case '-':
			left -= term();
			break;

		default:
			ts.putback(t);
			return left;
		}
	}
}