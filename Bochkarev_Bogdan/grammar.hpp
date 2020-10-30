//
//  grammar.hpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 10/1/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef grammar_hpp
#define grammar_hpp

#include <stdio.h>
#include <cmath>
#include "declare.hpp"
#include "scientific_options.hpp"
//#include "scientific_functions.hpp"
#include "token.hpp"


//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()
double primary();

//------------------------------------------------------------------------------

double sc_sqrt() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_scr> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d < 0) throw runtime_error("ERROR: <sc_scr> Negative value is imaginary;");
    return sqrt(d);
}

//------------------------------------------------------------------------------

double sc_sin() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_sin> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d == 0 || d == 180) return 0;       // return true zero
    return sin(d*M_PI/180);
}

//------------------------------------------------------------------------------

double sc_cos() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_cos> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d == 90 || d == 270) return 0;      // return 0 instead of 8.766e-11
    return cos(d*M_PI/180);
}

//------------------------------------------------------------------------------

double sc_tan() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_tan> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d == 90 || d == 270) throw runtime_error("ERROR: <sc_tan> Undefined;");
    if (d == 0 || d == 180) return 0;
    return tan(d*M_PI/180);
}

//------------------------------------------------------------------------------

double sc_cot() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_cot> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d == 0 || d == 180) throw runtime_error("ERROR: <sc_cot> Undefined;");
    if (d == 90 || d == 270) return 0;
    return 1/tan(d*M_PI/180);
}

//------------------------------------------------------------------------------

double sc_ln() {
    char ch;
    if (cin.get(ch) && ch != '(') throw runtime_error("ERROR: <sc_log> Expected '(', got something else instead;");
    cin.putback(ch);
    double d = primary();
    if (d <= 0) throw runtime_error("ERROR: <sc_log> Undefined for negative arguments;");
    return log(d);
}

//------------------------------------------------------------------------------

// grammar
double declaration() {
    Token t = ts.get();
    if (t.kind != name)
        throw runtime_error("ERROR: <sc_dec> Expected variable name;");
    string var_name = t.name;
    if (is_declared(var_name))
        throw runtime_error("ERROR: <sc_dec> Declared twice;");
    // cout << "I got name.";
    Token t2 = ts.get();
    if (t2.kind != '=')
        throw runtime_error("ERROR: <sc_dec> Missing '=' in declaration;");
    double d = expression();
    define_name(var_name, d);
    return d;
}

//------------------------------------------------------------------------------

double redefine() {
    Token t = ts.get();
    if (t.kind != name)
        throw runtime_error("ERROR: <sc_redef> Expected variable name;");
    string var_name = t.name;
    if (!is_declared(var_name))
        throw runtime_error("ERROR: <sc_redef> Variable doesn't exist;");
    if (var_name == "pi" || var_name == "e")
        throw runtime_error("ERROR: <sc_redef> Forbidden to redefine constants;");
    Token t2 = ts.get();
    if (t2.kind != '=')
        throw runtime_error("ERROR: <sc_redef> Missing '=' in redifinition;");
    double d = expression();
    set_value(var_name, d);
    return d;
}

//------------------------------------------------------------------------------

double statement() {
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration();
        case set:
            return redefine();
        default:
            ts.putback(t);
            return expression();
    }
}

//------------------------------------------------------------------------------
// deal with numbers and parentheses

double primary() {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            // cout << "Got here\n";
            double d = expression();
            t = ts.get();
            if (t.kind != ')') {
                throw runtime_error("ERROR: Expected ')', got something else instead;");
            }
            return d;
        }
        case number: {
            return t.value;
        }
        case name: {
            return get_value(t.name);
        }
        case '-': {
            return -primary();
        }
        case '+': {
            return primary();
        }
        case '!': {
            double d = primary();
            if (trunc(d) != d) {
                throw runtime_error("ERROR: Factorial is undefined for non-integers;");
            }
            return int(tgamma(d+1));
        }
        case square_root:
            return sc_sqrt();
        case c_sin:
            return sc_sin();
        case c_cos:
            return sc_cos();
        case c_tan:
            return sc_tan();
        case c_cot:
            return sc_cot();
        case c_ln:
            return sc_ln();
        default: {
            throw runtime_error("ERROR: Expected primary expression;");
        }
    }
}

//------------------------------------------------------------------------------
// deal with *, /, ^, and %
double term() { // Работает с операциями *, / и %
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
            case '*': {
                left *= primary();
                t = ts.get();
                break;
            }
            case '/': {
                double d = primary();
                if (d == 0) {
                    throw runtime_error("ERROR: Dividing by zero is prohibited;");
                }
                left /= d;
                t = ts.get();
                break;
            }
            case '^': {
                double d = term();
                if (left < 0 && trunc(d) != d) throw runtime_error("ERROR: You can only raise negative number to the natural exponent;");
                if (left == 0 && d == 0) throw runtime_error("ERROR: 0^0 is undefined;");
                left = double(pow(left, d)); // fixme! "5^2^3-11/3;" returns int \\ fixed!
                t = ts.get();
                break;
            }
            case '%': {
                double d = primary();
                if (d == 0) throw runtime_error("ERROR: Dividing by zero is prohibited;");
                if (left > 0) left = fmod(left, d);
                else left = d + fmod(left, d);
                t = ts.get();
                break;
            }
            default: {
                ts.putback(t);
                return left;
            }
        }
    }
}

//------------------------------------------------------------------------------
// deal with + and -
double expression() {
    // cout << "r";
    double left = term();
    Token t = ts.get();
    while(true) {
        switch (t.kind) {
            case '+':
                left+=term();
                t = ts.get();
                break ;
            case '-':
                left-=term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}


#endif /* grammar_hpp */

