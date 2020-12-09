//
//  secant_method.hpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/18/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef secant_method_hpp
#define secant_method_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "function.hpp"
#include "Wrap.hpp"
using namespace std;
void secant(double a, double b, double epsy, double (*f)(double));
#endif /* secant_method_hpp */
