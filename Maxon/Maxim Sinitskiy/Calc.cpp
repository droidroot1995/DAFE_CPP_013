#include "Operations.h"

Token_stream ts;


int main()
try
{
    double val = 0;
    while (cin)
    {
        Token t = ts.get();

        if (t.kind == 'q') break;  
        if (t.kind == ';')      
            cout << "=" << val << '\n';
        else
            ts.putback(t);

        val = expression(ts);
    }
}
catch (exception& e)
{
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Oops: unknown exception!\n";
    return 2;
}
