//
// Created by Алексей Ячменьков on 04.11.2020.
//

#ifndef CALCUTE_TOKEN_STREAM_H
#define CALCUTE_TOKEN_STREAM_H

#include "TOKEN.h"
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string help = "help";
const string Exit = "exit";
const string showval = "show";
const string Sqrt = "sqrt";
const string Sin = "sin";
const string Cos = "cos";
const string Tan = "tg";
const string Cotan = "ctg";
const string Ln = "ln";
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char ci_sin = 'z';
constexpr char ci_cos = 'c';
constexpr char ci_tan = 't';
constexpr char ci_cot = 'u';
constexpr char ci_ln = 'l';
constexpr char sqt_rt = '|';
class Token_stream
{
    bool full{ false }; // is there a Token in the buffer?
    Token buffer{ '\0' }; // here is where we keep a Token put back using putback()
public:
    Token_stream () { } // make a Token_stream that reads from cin
    Token get (); // get a Token (get() is defined elsewhere)
    void putback (Token t); // put a Token back
    void ignore (char c);
};

#endif //CALCUTE_TOKEN_STREAM_H
