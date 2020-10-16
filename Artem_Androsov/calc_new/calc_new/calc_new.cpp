#include <iostream>
#include <vector>
#include "Grammar.h"
using namespace std;

Token_stream ts;

int main()
{
	try
	{
		while (cin)
		{
			cout << expression() << '\n';
		}
		keep_window_open();
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		cerr << "exception\n";
		keep_window_open();
		return 2;
	}
}