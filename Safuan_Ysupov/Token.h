#ifndef TOKEN_H // to connect a class
#define TOKEN_H
#include "std_lib_facilities.h"

class Token
{
public:
    char kind;
    double value;
    string name;
    // Initializes kind with the CH character
    Token(char ch) : kind{ ch } {}
    // Initializes kind and value
    Token(char ch, string n) : kind{ ch }, name{ n }  { }
    // Initializes kind and name
    Token(char ch, double val) : kind{ ch }, value{ val }  { }
};

#endif
