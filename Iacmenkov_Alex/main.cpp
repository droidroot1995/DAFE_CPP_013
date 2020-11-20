#include "FUNCTION.h"
int main (){
    try
    {
        cout << "Print 'help' for learn what you can use!" << endl;
        calculate();
        keep_window_open();
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "I'm sorry, unknown exception" << endl;
        return 2;
    }
}