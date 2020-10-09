//
//  correctness_checker.hpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/25/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef correctness_checker_hpp
#define correctness_checker_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
bool iscorrect(double root, double xn, double xk, double eps, double (*f)(double));
#endif /* correctness_checker_hpp */
