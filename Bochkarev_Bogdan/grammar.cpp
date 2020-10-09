//
//  grammar.cpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 10/1/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//



//#include "grammar.hpp"
//#include "token.hpp"
//
//double expression();    // declaration so that primary() can call expression()
//
////------------------------------------------------------------------------------
//
//// grammar
//double declaration() {
//    Token t = ts.get();
//    if (t.kind != name)
//        throw runtime_error("ERROR: <sc_dec> Expected variable name;\n");
//    string var_name = t.name;
//    if (is_declared(var_name))
//        throw runtime_error("ERROR: <sc_dec> Declared twice;\n");
//    // cout << "I got name.";
//    Token t2 = ts.get();
//    if (t2.kind != '=')
//        throw runtime_error("ERROR: <sc_dec> Missing '=' in declaration;\n");
//    double d = expression();
//    define_name(var_name, d);
//    return d;
//}
//
//double redefine() {
//    Token t = ts.get();
//    if (t.kind != name)
//        throw runtime_error("ERROR: <sc_redef> Expected variable name;\n");
//    string var_name = t.name;
//    if (!is_declared(var_name))
//        throw runtime_error("ERROR: <sc_redef> Variable doesn't exist;\n");
//    if (var_name == "pi" || var_name == "e")
//        throw runtime_error("ERROR: <sc_redef> Forbidden to redefine constants;\n");
//    Token t2 = ts.get();
//    if (t2.kind != '=')
//        throw runtime_error("ERROR: <sc_redef> Missing '=' in redifinition;\n");
//    double d = expression();
//    set_value(var_name, d);
//    return d;
//}
//
//double statement() {
//    Token t = ts.get();
//    switch (t.kind) {
//        case let:
//            return declaration();
//        case set:
//            return redefine();
//        default:
//            ts.putback(t);
//            return expression();
//    }
//}
//// deal with numbers and parentheses
//double primary() {
//    Token t = ts.get();
//    switch (t.kind) {
//        case '(': {
//            double d = expression();
//            t = ts.get();
//            if (t.kind != ')') {
//                throw runtime_error("= ERROR: Expected ')', got something else instead;\n");
//            }
//            return d;
//        }
//        case number: {
//            return t.value;
//        }
//        case name: {
//            return get_value(t.name);
//        }
//        case '-': {
//            return -primary();
//        }
//        case '+': {
//            return primary();
//        }
//        default: {
//            throw runtime_error("= ERROR: Expected primary expression;\n");
//        }
//    }
//}
//
////------------------------------------------------------------------------------
//
//// deal with *, /, ^, and %
//double term() { // Работает с операциями *, / и %
//    double left = primary();
//    Token t = ts.get();
//    while (true) {
//        switch (t.kind) {
//            case '*': {
//                left *= primary();
//                t = ts.get();
//                break;
//            }
//            case '/': {
//                double d = primary();
//                if (d == 0) {
//                    throw runtime_error("= ERROR: Dividing by zero is prohibited;\n");
//                }
//                left /= d;
//                t = ts.get();
//                break;
//            }
//            case '^': {
//                left = double(pow(left, term())); // fixme! "5^2^3-11/3;" returns int
//                t = ts.get();
//                break;
//            }
//            case '%': {
//                // left %= primary();
//                // t = ts.get();
//                break;
//            }
//            default: {
//                ts.putback(t);
//                return left;
//            }
//        }
//    }
//}
//
////------------------------------------------------------------------------------
//
// deal with + and -
