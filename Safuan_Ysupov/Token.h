#ifndef TOKEN_H // для подключения класса
#define TOKEN_H
#include "std_lib_facilities.h"

class Token
{
public:
    char kind;
    double value;
    string name;
    // Инициализирует kind символом ch
    Token(char ch) : kind{ ch } {}
    // Инициализирует kind и value
    Token(char ch, string n) : kind{ ch }, name{ n }  { }
    // Инициализирует kind и name
    Token(char ch, double val) : kind{ ch }, value{ val }  { }
};

#endif
