//
//  Wrap.hpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef Wrap_hpp
#define Wrap_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "bisection_method.hpp"
#include "secant_method.hpp"
#include "Newton_method.hpp"
#include "correctness_checker.hpp"

using namespace std;
//struct SolverResult;

enum class SolverMethod
{
    bisection,
    secant,
    newton
    // ...
};

struct SolverResult
{
    double root;
    bool valid;
    unsigned int stepsNumber;
    SolverMethod method;
    SolverResult() = delete;
};

int start(SolverMethod &method, double &a, double &b, double &accuracy);
void solve_equation (double a, double b, double eps, SolverMethod method, double (*f)(double));
void print_results (SolverResult res);
#endif /* Wrap_hpp */
