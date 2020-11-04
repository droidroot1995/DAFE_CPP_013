#ifndef CALCULATEPROCESS_H
#define CALCULATEPROCESS_H

#include "printHelp.h"
#include "variables.h"

extern Token_stream ts; // we represent expressions as a stream of tokens
extern Symbol_table symbol_table;


double setValueFunc(Token& token);
double sqrtFunc();
double powFunc();

double expression ();
double statement();
double primary();
double term();

double declaration();

void clean_up_mess ();
void calculate ();

#endif // CALCULATEPROCESS_H
