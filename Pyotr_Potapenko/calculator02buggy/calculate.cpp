#include "token.h"
#include "calculate.h"

Token_stream ts;

/// deal with numbers and parentheses
double primary ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':          // handle '(' expression ')'
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("')' expected");
    return d;
  }

  case '8':          // we use '8' to represent a number
    return t.value;

  default:
    error("primary expected");
  }
}


/// deal with *, /, and %
double term ()
{
  double left = primary();
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '*':
      left *= primary();
      t = ts.get();
      break;
    case '/':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left /= d;
      t = ts.get();
      break;
    }

    default:
      ts.putback(t);     // put t back into the token stream
      return left;
    }
  }
}


/// deal with + and -
double expression ()
{
  double left = term();  // read and evaluate a Term
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '+':
      left += term();    // evaluate Term and add
      t = ts.get();
      break;

    case '-':
      left -= term();    // evaluate Term and subtract
      t = ts.get();
      break;

    default:
      ts.putback(t);     // put t back into the token stream
      return left;       // finally: no more + or -: return the answer
    }
  }
}
