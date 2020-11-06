#include "calculate.h"

int main()
{
    try
    {
      Symbol_table v;
      v.define_name ("pi", 3.141592653589793, true);
      v.define_name ("e",  2.718281828459045, true);

      calculate(v);

      return 0;
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

}
