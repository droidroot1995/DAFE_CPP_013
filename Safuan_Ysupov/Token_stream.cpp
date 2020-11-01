#include "Token_stream.h"
#include "std_lib_facilities.h"
#include "help_func.h"
#include <algorithm>
#include "tolower.cpp"

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

string iname = "D:/Progs/DAFE_CPP_013/Safuan_Ysupov/calc_cin.txt";
ifstream ist{ iname };

Token Token_stream::get() //Reading from cin and composing Token
{
    if (full)         // do we already have a Token ready?
    {
        full = false;   // remove Token from buffer
        return buffer;
    }
    char ch;
    ist >> ch;  // note that >> skips whitespace (space, newline, tab, ...)

    switch (ch)
    {
    case print:    // for "print"
    case '|':
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case ',':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case '!':
        return Token{ ch };      // let each character represent itself
    case '.':                    // A floating point number can start with a dot
        // numeric literal:
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        ist.putback(ch);         // put digit back into the input stream
        double val;
        ist >> val;              // read a floating-point number
        return Token{ number, val };  // let '8' represent "a number"
    }
    default:
        if (isalpha(ch) || (ch == '_'))
        {
            string s;
            s += ch;
            while ((ist.get(ch)) && (isalpha(ch) || isdigit(ch) || (ch=='_')))
                s += ch;
            ist.putback(ch);

            if (s == pow_key)
                return Token{ pow_ };

            else if (s == sqrt_key)
                return Token{ sqrt_ };

            else if (s == log_key)
                return Token{ log10_ };

            else if (s == declkey)
                return Token{ let };

            else if (s == quitF)
                return Token{ quit };
            tolower(s);
            if (s == "help")      // if we need know, how work calculater
            {
                HELP();
                return print;
            }
            return Token{ name,s };
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c)
// The c symbol represents a type of token
{
    //First we check the buffer:
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // now we check the input data:
    char ch = 0;
    while (ist >> ch)
        if (ch = c) return;
}