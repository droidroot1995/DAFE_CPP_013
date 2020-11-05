//
// Created by Алексей Ячменьков on 04.11.2020.
//
#ifndef CALCUTE_TOKEN_H
#define CALCUTE_TOKEN_H
#include <iostream>
#include <cmath>
#include "std_lib_facilities.h"
using namespace std;
struct Token
{
    char kind;  // what kind of token
    double value;  // for numbers: a value
    string name;
    Token (char ch)  // make a Token from a char
            : kind{ ch }, value{ 0 }
    { }
    Token (char ch, double val) // make a Token from a char and a double
            : kind{ ch }, value{ val }
    { }
    Token(char ch, string n)
            : kind{ch}, name{n}
    { }
};
#endif //CALCUTE_TOKEN_H
