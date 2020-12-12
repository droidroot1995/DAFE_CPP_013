#pragma once
#include "std_lib_facilities.h"


class Token
{
public:
    char kind;        
    double value;   

    Token(char ch)
        : kind{ ch }, value{ 0 }  { }

    Token(char ch, double val)
        : kind{ ch }, value{ val }  { }
};


class Token_stream
{
public:
    Token_stream();   

    Token get();
    void putback(Token t);

private:
    bool full{ false };  
    Token buffer;        
};