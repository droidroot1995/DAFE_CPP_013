//
//  Wrap.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "Wrap.hpp"

int start(SolverMethod &method, double &a, double &b, double &accuracy) {
    // Choosing solving method
    cout << "What method do you prefer to solve this equation?\n";
    cout << "Enter number of method:\n\
             1 - Bisection method;\n\
             2 - Secant method;\n\
             3 - Newton's method;\n";
    int ans;
    cin >> ans;
    switch (ans){
        case 1: method = SolverMethod::bisection; break;
        case 2: method = SolverMethod::secant; break;
        case 3: method = SolverMethod::newton; break;
        default:
            cerr << "Incorrect code was given";
            return 1;
    }
    
    
    // Choosing other parameters
    string ta, tb, tacc; //trying to get a, b, accuracy
    cout << "Please, choose the start of the segment: "; cin >> ta;
    cout << "Please, choose the end of the segment: "; cin >> tb;
    cout << "Please, choose the precision of calculation: "; cin >> tacc;
    try {
        a = stod(ta);
        b = stod(tb);
        accuracy = stod(tacc);
    } catch (invalid_argument) {
        cerr << "\nInvalid parameters were given: did you enter nonnumeric symbols?";
        return 2;
    }
    
    return 0;
}

void solve_equation(double a, double b, double eps, SolverMethod method, double (*f)(double))
{
    switch (method){
        case SolverMethod::bisection: return bisection(a, b, eps, f);
        case SolverMethod::secant: return secant(a, b, eps, f);
        case SolverMethod::newton: return newton(a, b, eps, f);
    }
    cout << "unreachable code point";
    return;
}

void print_results(SolverResult res) {
    string method_name;
    switch (res.method)
    {
        case SolverMethod::bisection: method_name = "bisection method"; break;
        case SolverMethod::secant: method_name = "secant method"; break;
        case SolverMethod::newton: method_name = "Newton's method"; break;
        default:
            cout << "Unreachable code point";
            return;
    }
    
    if (res.valid) {
        cout <<"The root of the equation is "<< res.root <<"\nUsing " << method_name << " it took " << res.stepsNumber <<" steps for calculation"<< endl;
    } else {
        cout <<"Root was not found"<< endl;
    }
}
