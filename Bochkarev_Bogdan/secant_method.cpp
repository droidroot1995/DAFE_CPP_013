//
//  secant_method.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "secant_method.hpp"
void secant(double a, double b, double epsy, double (*f)(double)) {
    unsigned steps = 0;
    double xn = a;
    double xk = b;
    while (abs(a - b) > epsy && steps < 2000) {
        double fa = f(a);
        double fb = f(b);
        if (fb - fa == 0.){
            cout << "Error!";
            return;
        }
        double temp = b;
        b = a - fa * (b - a) / (fb - fa);
        a = temp;
        ++steps;
    }
    bool correct = iscorrect(b, xn, xk, epsy, f);
    SolverResult r{b, correct, steps, SolverMethod::secant};
    print_results(r);
}
