#include "std_lib_facilities.h"

#include "calculateProcess.h"

int main ()
{
    try
    {
        define_name("pi", 3.141592653589793);
        define_name("e",  2.718281828459045);

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
