//
//  Newton_method.hpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef Newton_method_hpp
#define Newton_method_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "function.hpp"
#include "Wrap.hpp"
using namespace std;
void newton(double a, double b, double eps, double (*f)(double));
#endif /* Newton_method_hpp */
