#include "Grammar2.h"

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (cin)
	try
	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
		{
			t = ts.get();
		}
		if (t.name == quitkey)
		{
			return;
		}
		ts.putback(t);
		cout << result << statement() << '\n';
	}
	catch(exception& e)
	{
		cerr << e.what() << '\n';
		clean_up_mess();
	}
}