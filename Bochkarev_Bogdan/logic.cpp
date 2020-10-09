//
//  logic.cpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "logic.hpp"
#include "token.hpp"
#include "grammar.hpp"

// logic
//------------------------------------------------------------------------------
void init() {
    define_name("pi", M_PI);
    define_name("e", exp(1));
}

void calculate() {
    cout << welcome << endl;
    cin.get();
    cin.get();
    init();
    while (cin) {
        try {
            cout << prompt;  // waiting for input
            Token t = ts.get();
            while (t.kind==print) {
                t = ts.get();
            }
            if (t.kind == quit) return; // 'q' for quit
            ts.putback(t);
            cout << result << statement() << '\n';   // printing out the result
        }
        catch (exception& e) {
            cerr << e.what() << '\n';
            ts.ignore(print);
//            cout << "Got here\n";
        }
    }
}
