#ifndef VARIABLES_H
#define VARIABLES_H

#include "std_lib_facilities.h"

struct Variable
{
  string name;
  double value;
  bool isConstant;

  Variable (string n, double v)
    : name{ n }, value{ v }, isConstant{false}
  { }

  Variable (string n, double v, bool c)
    : name{ n }, value{ v }, isConstant{c}
  { }
};

struct Symbol_table
{
    vector<Variable> var_table; // the place where we store our variables

    double get(string s)
    {
      for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
          return var_table[i].value;

      error("get: undefined name ", s);
    }

    void set(string s, double d)
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

    bool is_declared(string s)
    {
      for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s) return true;
      return false;
    }

    double define(string var, double val)
    {
      if (is_declared(var)) {
          // set_value(var, val);
          error(var, " declared twice");
      }

      var_table.push_back (Variable{ var, val });

      return val;
    }

    double define(string var, double val, bool isConstant)
    {
      if (is_declared(var)) {
          // set_value(var, val);
          error(var, " declared twice");
      }

      var_table.push_back (Variable{ var, val, isConstant });

      return val;
    }
};

#endif // VARIABLES_H
