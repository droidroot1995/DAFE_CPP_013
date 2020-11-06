#include "variables.h"
#include "tokenStream.h"

Symbol_table symbol_table;
Token_stream ts;

double Symbol_table::get(string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d)
{
  for (int i = 0; i < var_table.size(); ++i)
  {
    if (var_table[i].name == s)
    {
      if (var_table[i].isConstant) {
          error(s + " is constant and can't be changed!");
      }
      var_table[i].value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s) return true;
  return false;
}

double Symbol_table::define(string var, double val)
{
  if (is_declared(var)) {
      // set_value(var, val);
      error(var, " declared twice");
  }

  var_table.push_back (Variable{ var, val });

  return val;
}

double Symbol_table::define(string var, double val, bool isConstant)
{
  if (is_declared(var)) {
      // set_value(var, val);
      error(var, " declared twice");
  }

  var_table.push_back (Variable{ var, val, isConstant });

  return val;
}