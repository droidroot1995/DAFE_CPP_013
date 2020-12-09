//
//  define_consts.hpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef define_consts_hpp
#define define_consts_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <map>
using namespace std;

const string welcome = "Welcome to Calculator 2.0 by Bogdan Bochkarev.\nIt deals with operations +, -, *, /, %, ^ and !.\nTo calculate factorial, please write '!' sign BEFORE number.\nGot not you wanted? Arrange parenthesis!\nUse English characters only!\nWrite ';' sign and 'Return' key to show the result of inputed expression.\nWrite 'q' or 'exit' to quit the program.\nGot stucked? Enter ';' and return key, it must help.\nIt supports the following algebraic functions: sin(x), cos(x), tan(x) or tg(x), cot(x) or ctg(x), ln(x) or log(x) and sqrt(x). Parenthesis are obligatory!\nIt also deals with variables. Use the keyword 'let' var_name = var_value to initialize your variable, and 'set' to change its value.\nPi and e constants are available and it's prohibited to change them.\n\nPlease press any key to start.";
const string wellcum = welcome;
const string declkey = "let";
const string chankey = "set";
const string sqrtkey = "sqrt";
const string sinkey = "sin";
const string coskey = "cos";
const string tankey = "tan";
const string tankeyru = "tg";
const string cotkey = "cot";
const string cotkeyru = "ctg";
const string lnkey = "ln";
const string logkey = "log";
const string prompt = "> ";
const string result = "= ";
const string exitkey = "exit";
const char quit = 'q';
// const char exit = 'e';
const char print = ';';
const char number = '8';
const char let = 'L';
const char set = 'S';
const char name = 'a';
const char c_sin = 's';
const char c_cos = 'c';
const char c_tan = 't';
const char c_cot = 'u';
const char c_ln = 'l';
const char square_root = '^';

#endif /* define_consts_hpp */
