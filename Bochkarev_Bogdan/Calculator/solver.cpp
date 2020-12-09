//
//  main.cpp
//  Equation solver
//
//  Created by Bogdan Bochkarev on 9/11/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//
#include "solver.h"


int solver() {
    double xn, xk, epsy;
    SolverMethod m;
    int retcode = start(m, xn, xk, epsy);
    cout << setprecision(-int(log10(epsy))) << fixed;
    if (!retcode){
        solve_equation(xn, xk, epsy, m, f);
    }
    else {
        cout << "\nError. End of process.\n";
    }
    return 0;
}
