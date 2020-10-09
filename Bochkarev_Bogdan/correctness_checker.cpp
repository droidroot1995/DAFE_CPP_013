//
//  correctness_checker.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/25/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "correctness_checker.hpp"
bool iscorrect(double root, double xn, double xk, double eps, double (*f)(double)) {
    // cout << "\nDEBUG: " << (f(root) >= 0 + eps) << (f(root) <= 0 - eps) << (root < xn) << (root > xk) << endl << root << endl << f(root) << endl;
    
    return not (f(root) >= 0 + eps || f(root) <= 0 - eps || root < xn || root > xk);
}
