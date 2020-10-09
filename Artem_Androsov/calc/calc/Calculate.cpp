#include <iostream>
#include "std_lib_facilities.h"
#include "TokenStr.h"
#include "What.h"

extern Token_stream ts;

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
