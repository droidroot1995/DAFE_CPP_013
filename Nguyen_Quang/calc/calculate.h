#ifndef calculateprogcess_h
#define calculateprogcess_h

#include "printHelp.h"
#include "variables.h"
#include "tokenStream.h"
#include "keys.h"

extern Token_stream ts; // we represent expressions as a stream of tokens
extern Symbol_table symbol_table;


double setValueFunc(Token& token);
double sqrtFunc();
double powFunc();
double logFunc();

double expression ();
double statement();
double primary();
double term();

double declaration();

void clean_up_mess ();
void calculate ();

#endif