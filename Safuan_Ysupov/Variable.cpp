#include "Variable.h"

vector<Variable> var_table;

double get_value(string s)
//Возвращает значение переменной с именем s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
// Присваивает объекту s типа Variable значение d
{
    for (Variable& v : var_table)
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    error("set: неопределённая переменная ", s);
}

bool is_declared(string var)
//Есть ли переменная var в векторе var_table?
{
    for (const Variable v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val)
// Добавляем пару (var,val) в вектор var_table
{
    if (is_declared(var)) error(var, " повторное объявление11 ");
    var_table.push_back(Variable{ var, val });
    return val;
}