//
//  main.cpp
//  Calculator 1.3
//
//  Created by Bogdan Bochkarev on 10/5/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include <iostream>
#include "solver.h"
#include "calculator.h"

int main(int argc, const char * argv[]) {
    cout << "Press 1 to launch the calculator or 2 to solve the equation: ";
    int z; cin >> z; cout << endl << endl;
    switch (z) {
        case 1: {
            calculator();
            break;
        }
        case 2: {
            solver();
            break;
        }
        default:
            break;
    }

    cout << "Quiting...\nThanks for using this program, bye!\n\n";
    return 0;
}
