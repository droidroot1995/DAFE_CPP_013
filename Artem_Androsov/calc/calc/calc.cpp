#include <iostream>
#include "std_lib_facilities.h"
#include "TokenStr.h"
#include "Fun.h"
#include "What.h"
#include "Calculate.h"
using namespace std;

Token_stream ts;

vector<Variable> var_table;

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
