#include <iostream>
#include "std_lib_facilities.h"
#include "TokenStr.h"
#include "Fun.h"
#include "Grammar.h"
using namespace std;

Token_stream ts;

vector<Variable> var_table;

double declaration()
{
	Token t = ts.get();
	if (t.kind != name)
		error("name expected in declaration");

	string var = t.name;
	if (is_declared(var))
		error(var, " declared twice");

	t = ts.get();
	if (t.kind != '=')
		error("'=' missing in declaration of ", var);

	return define_name(var, expression());
}


double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}


void clean_up_mess()
{
	ts.ignore(print);
}


void calculate()
{
	while (true)
		try
	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit) return;

		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}


int main()
try
{
	define_name("pi", 3.141592653589793);
	define_name("e", 2.718281828459045);

	calculate();
}
catch (exception& e)
{
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Oops, unknown exception" << endl;
	return 2;
}
