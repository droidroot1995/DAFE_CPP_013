#ifndef variables_h
#define variables_h

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

    double get(string s);
    void set(string s, double d);
    bool is_declared(string s);
    double define(string var, double val);
    double define(string var, double val, bool isConstant);
};

#endif