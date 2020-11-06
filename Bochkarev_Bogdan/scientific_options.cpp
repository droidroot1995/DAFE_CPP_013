//
//  scientific_options.cpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "scientific_options.hpp"

// scientific stuff
//------------------------------------------------------------------------------

static vector<Variable> var_table;

//------------------------------------------------------------------------------

double get_value(string var_name) {
//    for (int i = 0; i < var_table.size(); i++) {
//        cout << var_table[i].name << "; " << var_table[i].value << endl;
//    }
    for (Variable& v : var_table) {
        // cout << "got here 'for'";
        if (v.name == var_name) {
            // cout << "got here 'if'";
            return v.value;
        }
    }
    throw runtime_error("ERROR: <sc_get> Undefined variable name;");
}

//------------------------------------------------------------------------------

void set_value(string var_name, double var_value) {
    for (Variable& v : var_table) {
        if (v.name == var_name) {
            v.value = var_value;
            return;
        }
    }
    throw runtime_error("ERROR: <sc_set> Undefined variable name;");
}

//------------------------------------------------------------------------------

bool is_declared(string var) {
    // Is there a variable named var in the vector?
    for (const Variable& v : var_table) if (v.name == var) return true;
    return false;
}

//------------------------------------------------------------------------------

double define_name(string var, double val) {
    var_table.push_back(Variable{var,val});
    // cout << "Pushed";
    return val;
}
