//
//  function.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "function.hpp"
#include <Python/Python.h>
#include <fstream>

string s;

void replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return;
    str.replace(start_pos, from.length(), to);
}

void set_function(string func) {
    s = func;
    replace(s, "^", "**");
    cout << s;
}

double f(double x) {
//    Py_Initialize();
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("from math import *");
//    string r = "def f(x):\n    return " + s;
//    PyRun_SimpleString(r.c_str());
//    string outv = "outv = f(" + to_string(x) + string(")");
//    PyRun_SimpleString(outv.c_str());
//    PyRun_SimpleString("f = open('Buffer.txt', 'w')");
//    PyRun_SimpleString("f.write(outv)");
//    PyRun_SimpleString("f.close()");
//    Py_Finalize();
//    ifstream evaluated;
//    int res;
//    evaluated.open("Buffer.txt");
//    evaluated >> res;
//    evaluated.close();
//    return res;
//    string i;
//    cin >> i;
//    set_function(i);
    return 5*x - pow(exp(1), x);
}
