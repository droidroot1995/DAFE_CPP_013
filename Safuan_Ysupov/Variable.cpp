#include "Variable.h"

vector<Variable> var_table;

double get_value(string s)
// Returns the value of a variable named s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
// Assigns the value d to an s object of type Variable
{
    for (Variable& v : var_table)
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}

bool is_declared(string var)
// Is there a var variable in the var_table vector?
{
    for (const Variable v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val)
// Adding a pair (var, val) to the var_table vector
{
    if (is_declared(var))
        error(var, " repeat ad ");
    var_table.push_back(Variable{ var, val });
    return val;
}