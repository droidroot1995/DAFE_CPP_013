#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"

const char number = '8'; // t.kind==number означает, что t - число
const char quit = 'q';  //  t.kind==quit означает, что t - лексема выхода
const char print = ';'; // t.kind==print означает, что t - лексема печати 
const string prompt = "> "; // Используется для указания на то,
const string result = "= "; // что далее следует результат
const char name = 'a';
const char let = 'L';
const string declkey = "let";

class Token_stream
{
public:
    Token get();            //Считывает лексему
    void putback(Token t);  //Возвращает лексему в поток
    void ignore(char c);    //Отбрасывает символы до
    Token_stream() {};      //до символа включительно
private:
    bool full{ false };  // is there a Token in the buffer?
    Token buffer{ '\0' };        // here we keep a Token put back using putback()

};

#endif
