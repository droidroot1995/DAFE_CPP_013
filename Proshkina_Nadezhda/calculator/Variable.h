#ifndef VARIABLE_H
#define VARIABLE_H

#include "Token.h"

struct Variable
{
  string name;
  double value;
  bool const1;

  Variable (string n, double v)
    : name{ n }, value{ v }, const1{ false} { }

  Variable (string n, double v, bool c)
    : name{ n }, value{ v }, const1{ c } { }
};

class Symbol_table
{
vector<Variable> var_table;

public:
    double get_value (string s);
    void set_value (string s, double d);
    bool is_declared (string s);
    double define_name (string var, double val, bool const1);
};

#endif
