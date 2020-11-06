#include "Variable.h"

double expression(Token_stream& ts, Symbol_table& var_table);

double primary (Token_stream& ts, Symbol_table& var_table)
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':
  {
    double d = expression(ts, var_table);
    t = ts.get();
    if (t.kind != ')')
      error("'(' expected");
    return d;
  }
    
  case '{':
  {
    double d = expression(ts, var_table);
    t = ts.get();
    if (t.kind != '}')
      error("'}' expected");
    return d;
  }

  case '-':
    return -primary(ts, var_table);

  case '+':
    return +primary(ts, var_table);

  case number:
    return t.value;

  case name:
  {
    Token n = ts.get();
    if (n.kind == '=')
    {
        double d = expression(ts,var_table);
        var_table.set_value(t.name, d);
        return d;
    }
    else
    {
        ts.putback(n);
        return var_table.get_value(t.name);
    }
  }

  default:
    error("primary expected");
  }
}

double term (Token_stream& ts, Symbol_table& var_table)
{
    double left = primary(ts, var_table);
    while (true)
    {
      Token t = ts.get();

      switch (t.kind)
      {
      case '*':
        left *= primary(ts, var_table);
        break;

      case '/':
      {
        double d = primary(ts, var_table);
        if (d == 0) error("divide by zero");
        left /= d;
        break;
      }

      case '%':
      {
        double d = primary(ts, var_table);
        if (d == 0) error(" %: divide by zero");
        left = fmod(left,d);
        break;
      }

      case '^':
      {
        double d = primary(ts, var_table);
        left = pow(left,d);
        break;
      }

      default:
        ts.putback(t);
        return left;
      }
    }
}


double expression(Token_stream& ts, Symbol_table& var_table)
{
    double left = term(ts, var_table);
    while(true)
    {
        Token t = ts.get();

        switch(t.kind)
        {
         case '+':
            left += term(ts, var_table);
            break;

         case '-':
            left -= term(ts, var_table);
            break;

         default:
            ts.putback(t);
            return left;
        }

    }
}


double declaration(Token_stream& ts, Token n, Symbol_table& var_table)
{
    Token t = ts.get();

    if (t.kind != name)
        error("variable_expected");

    string var = t.name;
    Token t2 = ts.get();

    if (t2.kind != '=')
        error("= missing declaration of ", var);
    double d = expression(ts, var_table);

    var_table.define_name(var, d, n.kind == let);
    return d;
}






double statement(Token_stream& ts, Symbol_table& var_table)
{
   Token t = ts.get();
   switch (t.kind)
   {
    case let:
       return declaration(ts, t.kind,var_table);
       break;
    default:
       ts.putback(t);
       return expression(ts, var_table);
   }
}


void calculate(Symbol_table& var_table)
{
    Token_stream ts;
    while (true)
    {
      try
      {
        cout<<prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get();
        if (t.kind == quit)
            return;
        ts.putback(t);
        cout<<result<<statement(ts, var_table)<<'\n';
      }
      catch(exception& e)
      {
        cout<<e.what()<<'\n';
        clean_up_mess(ts);
      }
    }
}
