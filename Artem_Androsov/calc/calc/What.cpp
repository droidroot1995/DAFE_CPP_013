#include <iostream>
#include "std_lib_facilities.h"
#include "TokenStr.h"
#include "Fun.h"
#include "Grammar.h"

extern Token_stream ts;

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