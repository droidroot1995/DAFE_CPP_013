#include "Variable.h"

double Symbol_table:: get_value (string s)
{
  for (auto v : var_table)
    if (v.name == s)
      return v.value;

  error("get: undefined name ", s);
}

void Symbol_table:: set_value (string s, double d)
{
  for (auto v : var_table)
  {
    if (v.name == s)
    {
      v.value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool Symbol_table:: is_declared (string s)
{
  for (auto v : var_table)
    if (v.name == s) return true;
  return false;
}

double Symbol_table:: define_name (string var, double val, bool const1)
{
  if (is_declared(var))
    for (auto v : var_table)
        if (v.name == var)
        {
            v.value = val;
            v.const1 = const1;
        }

  var_table.push_back(Variable{var, val, const1});
  return val;
}
