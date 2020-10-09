//
//  bisection_method.hpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef bisection_method_hpp
#define bisection_method_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "function.hpp"
#include "Wrap.hpp"
using namespace std;
void bisection(double xn, double xk, double epsy, double (*f)(double));

#endif /* bisection_method_hpp */
