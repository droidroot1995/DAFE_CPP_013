#include "token.h"
#include "calculate.h"

extern Token_stream ts;

int main ()
try
{
  double val;
  while (cin)
  {
    Token t = ts.get();

    if (t.kind == 'q') break;  // 'q' for quit
    if (t.kind == ';')         // ';' for "print now"
      cout <<"="<< val <<'\n';
    else
      ts.putback(t);

    val = expression();
  }
}
catch (exception& e)
{
  cerr <<"error: "<< e.what() <<'\n';
  return 1;
}
catch (...)
{
  cerr <<"Oops: unknown exception!\n";
  return 2;
}
