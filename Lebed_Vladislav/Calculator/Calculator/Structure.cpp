#include "Structure.h"

#include "Consts.h"
#include "Token.h"
#include "Variable.h"


double fctr(double x) // Factorial
{
    if (x < 0)
    {
        error("Factorial(value), value < 0 - Wrong operation");
    }
    if (x != round(x))
    {
        error("Factorial(value), value - Natural number");
    }
    if (x == 0)
        return 1;
    else
    {
        return x * fctr(x - 1);
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != name)
    {
        error("name expected in declaration");
    }
    string var = t.name;

    if (is_declared(var))
    {
        error(var, " declared twice");
    }

    t = ts.get();
    if (t.kind != '=')
    {
        error("'=' missing in declaration of ", var);
    }

    return define_name(var, expression());
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' expected");
        }
        return d;
    }
    case '^':
    {
        double d = expression();
        if (d < 0)
        {
            error("sqrt(value), value < 0 - Wrong operation");
        }
        return sqrt(d);
    }
    case '!':
    {
        double d = expression();
        return fctr(d);
    }
    case '-':
        return -primary();
    case '+':
        return +primary();

    case number:
        return t.value;

    case name:
        return get_value(t.name);

    default:
        error("primary expected");
    }
}

double term()
{
    double left = primary();
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;

        case '/':
        {
            double d = primary();
            if (d == 0)
            {
                error("divide by zero");
            }
            left /= d;
            break;
        }

        case '%':
        {
            double d = primary();
            if (d == 0)
            {
                error("Divide by zero, ( % )");
            }
            left = fmod(left, d);
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '+':
            left += term();
            break;

        case '-':
            left -= term();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}
