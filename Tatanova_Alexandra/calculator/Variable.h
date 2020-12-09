#ifndef VARIABLE_H
#define VARIABLE_H
#include "std_lib_facilities.h"
//#include <vector>
//#include <string>


struct Variable
{
  string name;
  double value;

  Variable ( string n, double v)
    : name{ n }, value{ v }
  { }
};

double get_value (string s);
void set_value (string s, double d);
bool is_declared (string s);
double define_name (string var, double val);


#endif // VARIABLE_H
