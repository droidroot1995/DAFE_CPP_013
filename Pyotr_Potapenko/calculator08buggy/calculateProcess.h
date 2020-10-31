#ifndef CALCULATEPROCESS_H
#define CALCULATEPROCESS_H

#include "printHelp.h"
#include "variables.h"


Token_stream ts; // we represent expressions as a stream of tokens
Symbol_table symbol_table;

double expression ();

double statement();

double setValueFunc(Token& token);
double sqrtFunc();
double powFunc();

double primary ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("')' expected");
    return d;
  }

  case '-':
    return -primary();
  case '+':
    return +primary();

  case number:
    return t.value;

  case name:
    return setValueFunc(t);

  case sqrtKey:
     return sqrtFunc();

  case powKey:
      return powFunc();

  default:
    error("primary expected");
  }
}


double term ()
{
  double left = primary();
  while (true)
  {
    Token t = ts.get();
    switch (t.kind)
    {
    case '*':
      left *= primary();
      break;

    case '/':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left /= d;
      break;
    }

    case '%':
    {
      int il = narrow_cast<int> (left) ;
      int i2 = narrow_cast<int> (primary());
      if (i2 == 0) error("% : divide by zero");
      left = il % i2;
      // t = ts.get();
      break;
    }

    default:
      ts.putback(t);
      return left;
    }
  }
}


double expression ()
{
  double left = term();
  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '+':
      left += term();
      break;

    case '-':
      left -= term();
      break;

    default:
      ts.putback(t);
      return left;
    }
  }
}


double declaration ()
{
  Token t = ts.get();
  if (t.kind != name)
    error("name expected in declaration");

  string var = t.name;
  if (symbol_table.is_declared(var))
    error(var, " declared twice");

  t = ts.get();
  if (t.kind != '=')
    error("'=' missing in declaration of ", var);

  return symbol_table.define(var, expression());
}

double sqrtFunc()
{
    Token token = ts.get();
    if (token.kind != '(')
        error("there must be '(' before 'x' parameter in sqrt(x)");

    double x = expression();

    if (x < 0)
        error("expression under sqrt() is below zero");

    token = ts.get();
    if (token.kind != ')')
        error("there must be ')' after 'x' parameter in sqrt(x)");

    return sqrt(x);
}

double powFunc()
{
    Token token = ts.get();
    if (token.kind != '(')
        error("there must be '(' before first parameter in pow(x, y)");

    double x = expression();

    token = ts.get();
    if (token.kind != ',')
        error("there must be ',' between first and second parameter in pow(x, y)");

    double y = expression();

    token = ts.get();
    if (token.kind != ')')
        error("there must be ')' after second parameter in pow(x, y)");

    narrow_cast<int>(y);

    return pow(x, y);
}

double setValueFunc(Token& nameToken) {
    string name = nameToken.name;
    Token token = ts.get();
    if (token.kind != '=') {
        ts.putback(token);
        return symbol_table.get(name);
    }
    double value = statement();
    symbol_table.set(name, value);
    return value;
}

double statement ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case let:
    return declaration();
  default:
    ts.putback(t);
    return expression();
  }
}


void clean_up_mess ()
{
  ts.ignore (print);
}


void calculate ()
{
  while (cin)
  try
  {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print)
      t = ts.get();
    if (t.kind == help) continue;
    if (t.kind == quit) return;

    ts.putback(t);
    cout << result << statement() << endl;
  }
  catch (runtime_error& e)
  {
    cerr << e.what() << endl;
    clean_up_mess();
  }
}


#endif // CALCULATEPROCESS_H
