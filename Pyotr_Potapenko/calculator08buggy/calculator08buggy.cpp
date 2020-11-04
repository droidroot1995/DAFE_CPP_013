#include "std_lib_facilities.h"
#include "calculate.h"

extern Symbol_table symbol_table;
extern Token_stream ts;

int main ()
{
    try
    {
        symbol_table.define("pi", 3.141592653589793 ,true);
        symbol_table.define("e",  2.718281828459045, true);
        symbol_table.define("k", 1000);

        cout << "Use \"" + helpString + "\" if you need help.\n";
        calculate();

        keep_window_open();
        return 0;
    }
    catch (exception& e)
    {
        cerr << "exception: " << e.what() << endl;
        keep_window_open("~~");
        return 1;
    }
    catch (...)
    {
        cerr << "Oops, unknown exception" << endl;
        keep_window_open("~~");
        return 2;
    }
}
