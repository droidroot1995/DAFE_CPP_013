#include "Token_stream.h"
#include "std_lib_facilities.h"

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

string iname = "D:/Progs/DAFE_CPP_013/Safuan_Ysupov/calc_cin.txt";
ifstream ist{ iname };

Token Token_stream::get() //Чтение из cin и составление Token 
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
    case quit:    // for "quit"
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token{ ch };      // let each character represent itself
    case '.':                    // Число с плавающей точкой может начинаться с точки
        // числовой литерал:
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        ist.putback(ch);         // put digit back into the input stream
        double val;
        ist >> val;              // read a floating-point number
        return Token{ number, val };  // let '8' represent "a number"
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while ((ist.get(ch)) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            ist.putback(ch);
            if (s == declkey)
                return Token{ let };
            return Token{ name,s };
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c)
// Символ с представляет разновидность лексем
{
    //Сначала проверяем буфер:
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    // теперь проверяем входные данные:
    char ch = 0;
    while (ist >> ch)
        if (ch = c) return;
}