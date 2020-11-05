//
// Created by Алексей Ячменьков on 04.11.2020.
//

#include "TOKEN_STREAM.h"
void Token_stream::putback (Token t) // The putback() member function puts its argument back into the Token_stream's buffer:
{
    if (full)
        error("`ERROR: putback() into a full buffer");
    buffer = t;
    full = true;
}
Token Token_stream::get ()
{
    if (full)
    {
        full = false;
        return buffer;
    }
    char ch;
    ch = getchar();
    while (ch == ' ')
        ch = getchar();
    switch (ch)
    {
        case print:
        case '(': // all those symbols represent themselves
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '^':
        case '!':
            return Token{ ch };
        case '\n':
            return Token{ print };
        case '.': // float number can start with '.'
        // numeric literal
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{ number, val };
        }
        default:
            if (isalpha(ch))
            {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch)|| ch =='_'))
                    s += ch;
                cin.putback(ch);
                if (s == declkey) return Token {let};
                else if (s == Sin) return Token{ci_sin};
                else if (s == Cos) return Token{ci_cos};
                else if (s == Tan) return Token{ci_tan};
                else if (s == Cotan) return Token{ci_cot};
                else if (s == Sqrt) return Token{sqt_rt};
                else if (s == Ln) return Token{ci_ln};
                else if (s == "con") return Token{ 'C' };
                else if (s == Exit) return Token{ quit };
                else if (s == help) return Token{ help[0] };
                else if (s == showval) return Token{showval[0]};
                return Token{ name, s };
            }
            error("ERROR: Bad token");
    }
}
void Token_stream::ignore (char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;
    char ch = getchar();
    while (ch){

        if (ch == '\n') ch = c;
        if (ch == c) return; ch = getchar();}
}