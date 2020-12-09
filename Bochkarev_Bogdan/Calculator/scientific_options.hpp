//
//  scientific_options.hpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef scientific_options_hpp
#define scientific_options_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Variable {
    public:
        string name;
        double value;
};

//extern vector<Variable> var_table;
double get_value(string var_name);
void set_value(string var_name, double var_value);
bool is_declared(string var);
double define_name(string var, double val);

#endif /* scientific_options_hpp */
