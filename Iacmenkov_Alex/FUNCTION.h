//
// Created by Алексей Ячменьков on 04.11.2020.
//

#ifndef CALCUTE_FUNCTION_H
#define CALCUTE_FUNCTION_H


#include "Variable.h"
#include "TOKEN_STREAM.h"
using namespace std;
double expression();
double primary();
double term();
double declaration (Token let_or_const);
double statement ();
void clean_up_mess ();
void printHelp();
void calculate();
#endif //CALCUTE_FUNCTION_H
