//
//  bisection_method.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "bisection_method.hpp"

void bisection(double xn, double xk, double epsy, double (*f)(double)) {
    double dx;
    double xi = 0.0;
    unsigned int steps = 0;
    double a = xn;
    double b = xk;
    
    if (f(xn) == 0) {
        cout << f(xn);
    }
    else if (f(xk) == 0) {
        cout << f(xk);
    }
    else {
        while (abs(xk - xn) > epsy && steps < 2000) {
            dx = (xk - xn) / 2;
            xi = xn + dx;
            if (f(xn) * f(xi) <= 0) {
                xk = xi;
            } else {
                xn = xi;
            }
            ++steps;
        }
    }
    // cout << "DEBUG: " << xi;
    bool correct = iscorrect(xi, a, b, epsy, f);    //fixme!
    SolverResult r{xi, correct, steps, SolverMethod::bisection};
    print_results(r);
}
