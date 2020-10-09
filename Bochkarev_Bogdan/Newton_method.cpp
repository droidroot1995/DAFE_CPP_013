//
//  Newton_method.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "Newton_method.hpp"
void newton(double a, double b, double eps, double (*f)(double)) {
    const double dx = eps * 0.01;
    unsigned steps = 0;
    double x = 0.5 * (a + b);
    double x0;
    do {
        x0 = x;
        double df = (f(x0 + dx) - f(x0)) / dx;
        if (df == 0.) {
            return;
        }
        x = x0 - f(x0) / df;
        ++steps;
    } while (abs(x - x0) > eps);
    bool correct = iscorrect(x, a, b, eps, f);
    SolverResult r{x, correct, steps, SolverMethod::newton};
    print_results(r);
}
