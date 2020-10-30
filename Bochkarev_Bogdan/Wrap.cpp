//
//  Wrap.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "Wrap.hpp"

int start(SolverMethod &method, double &a, double &b, double &accuracy) {
    cout << "Sorry, this version only solves equation f(x) = 0 where f(x) is defined in source code. That means, you can't solve equation, inputted from keyboard. We work on it, wait this feature in next versions.\nKeep in mind that this program only works correct if there's only one root (or zero) on the segment.\nf(x) = 5*x - pow(exp(1), x)\nNotice that some methods aren't able to give you the precision you want, which leads to rejecting it by correctness_checker(). Use other methods in that case.\n\n";
    // Choosing solving method
    cout << "What method do you prefer to solve this equation?" << endl;
    cout << "Enter number of method:\n\
             1 - Bisection method;\n\
             2 - Secant method;\n\
             3 - Newton's method;\n";
    int ans;
    cout << "Your choice: "; cin >> ans;
    switch (ans){
        case 1: method = SolverMethod::bisection; break;
        case 2: method = SolverMethod::secant; break;
        case 3: method = SolverMethod::newton; break;
        default:
            cerr << "Incorrect code was given." << endl;
            return 1;
    }

    // Choosing other parameters
    string ta, tb, tacc; //trying to get a, b, accuracy
    cout << "Please, choose the start of the segment: "; cin >> ta;
    cout << "Please, choose the end of the segment: "; cin >> tb;
    cout << "Please, choose the precision of calculation (format: 0.00001): "; cin >> tacc;
    try {
        a = stod(ta);
        b = stod(tb);
        accuracy = stod(tacc);
        if (accuracy <= 0 || a >= b) throw invalid_argument("");
    } catch (invalid_argument) {
        cerr << "\nInvalid parameters were given: did you enter non-numeric symbols or accuracy is not positive?" << endl;
        return 2;
    }
    return 0;
}

void solve_equation(double a, double b, double eps, SolverMethod method, double (*f)(double))
{
    switch (method) {
        case SolverMethod::bisection: return bisection(a, b, eps, f);
        case SolverMethod::secant: return secant(a, b, eps, f);
        case SolverMethod::newton: return newton(a, b, eps, f);
    }
    cout << "Unreachable code point.";
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
        cout << "The root of the equation is " << res.root << "\nUsing " << method_name << " it took " << res.stepsNumber << " steps for calculation" << endl;
    } else {
        cout << "Root was not found" << endl;
    }
}
