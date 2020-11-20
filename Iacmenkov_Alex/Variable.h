//
// Created by Алексей Ячменьков on 04.11.2020.
//

#ifndef CALCUTE_VARIABLE_H
#define CALCUTE_VARIABLE_H
#include "TOKEN.h"
struct Variable
{
    string name;
    double value;
    bool constant;
    Variable (string n, double v, bool c)
    : name{n}, value {v}, constant{c}
    {}
};
class Symbol_table{
private:
    vector<Variable> var_table;
public:
    double get_value (string s);
    void set_value (string s, double d);
    bool is_declared (string s);
    double define_name (string var, double val, bool con);
    void print_values();
};
#endif //CALCUTE_VARIABLE_H
