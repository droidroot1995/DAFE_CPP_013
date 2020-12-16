#include "Operations.h"


double expression(Token_stream &ts);


double primary(Token_stream &ts)
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':        
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }

    case '8':         
        return t.value;

    default:
        error("primary expected");
    }
}


double term(Token_stream &ts)
{
    double left = primary(ts);
    Token t = ts.get();    

    while (true)
    {
        switch (t.kind)
        {
        case '*': {
            left *= primary(ts);
            t = ts.get();
            break;
        }
        case '/':
        {
            double d = primary(ts);
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }

        default:
            ts.putback(t);     
            return left;
        }
    }
}


double expression(Token_stream &ts)
{
    double left = term(ts);
    Token t = ts.get();    

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(ts);   
            t = ts.get();
            break;

        case '-':
            left -= term(ts);   
            t = ts.get();
            break;

        default:
            ts.putback(t);    
            return left;      
        }
    }
}