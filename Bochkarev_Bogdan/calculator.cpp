//
//  main.cpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "calculator.h"

int calculator() {
    try {
        cout << setprecision(10) << fixed;
        calculate();
        return 0;
    }
    catch (exception& e) {
        cerr << e.what() << '\n';
        cout << "= An error ocured\n  Enter '~' to quit;\n";
        for(char ch; cin >> ch; ) // Чтение до ввода символа ~
            if (ch == '~') return 1;
        return 1;
    }
    catch (...) {
        cerr << "= Exception\n  Unknown issue;\n";
        for(char ch; cin >> ch; ) // Чтение до ввода символа ~
            if (ch == '~') return 2;
        return 2;
    }
}


