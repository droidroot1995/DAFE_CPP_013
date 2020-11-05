//
// Created by Алексей Ячменьков on 04.11.2020.
//

#include "FUNCTION.h"
Symbol_table syta;
Token_stream ts;
double primary ()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')')
                error("ERROR: ')' expected");
            return d;
        }
        case '-':
            return -primary();
        case '+':
            return +primary();
        case '!':
        {
            double d = primary();
            if (trunc(d) != d)
            {
                error("ERROR: Factorial is undefined for non-integers;");
            }
            return int(tgamma(d + 1));
        }
        case number:
            return t.value;
        case sqt_rt:
        {
            double d = primary();
            if( d < 0)
                error("ERROR: Negative value!");
            return sqrt(d);
        }
        case ci_sin:
        {
            double angl = primary();
            if (angl == 0 || angl == 180)
                return 0; // return true zero
            return sin(angl*M_PI/180);
        }
        case ci_cos:
        {
            double angl = primary();
            if (angl == 90 || angl == 270)
                return 0; // return 0 instead of 8.766e-11
            return cos(angl*M_PI/180);
        }
        case ci_tan:
        {
            double angl = primary();
            if (angl == 90 || angl == 270)
                error("ERROR: tan Undefined;");
            if (angl == 0 || angl == 180)
                return 0;
            return tan(angl*M_PI/180);
        }
        case ci_cot:
        {
            double angl = primary();
            if (angl == 0 || angl == 180)
                error("ERROR: cot Undefined;");
            if (angl == 90 || angl == 270)
                return 0;
            return 1/tan(angl*M_PI/180);
        }
        case ci_ln:
        {
            double d = primary();
            if (d <= 0)
                error("ERROR: ln Undefined for negative arguments;");
            return log(d);
        }
        case name:
        {
            Token following = ts.get();
            if (following.kind == '=')
            {
                double d = expression();
                syta.set_value(t.name, d);
                return d;
            }
            else
            {
                ts.putback(following);
                return syta.get_value(t.name);
            }
        }
        default:
            error("ERROR: OOps, primary expected");
    }
}
double term ()
{
    double left = primary();
    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
            case '*':
            {
                left *= primary();
                break;
            }
            case '/':
            {
                double d = primary();
                if (d == 0)
                    error("OOps, divide by zero!");
                left /= d;
                break;
            }
            case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(primary());
                if (i2 == 0)
                    error("OOps, divide by zero!");
                left = i1%i2;
                break;
            }
            case '^':
            {
                double d = term();
                if (left < 0 && trunc(d) != d)
                    error("ERROR: You can only raise negative number to the natural exponent;");
                if (left == 0 && d == 0)
                    error("ERROR: 0^0 is undefined;");
                left = double(pow(left, d));
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}
double expression ()
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
double declaration (Token let_or_const)
{
    Token t = ts.get();
    if (t.kind != name)
        error("ERROR: name expected in declaration");
    string var = t.name;
    if (syta.is_declared(var))
        error(var, "ERROR: declared twice");
    t = ts.get();
    if (t.kind != '=')
        error("ERROR: '=' missing in declaration of ", var);
    if (let_or_const.kind == let)
        return syta.define_name (var, expression(), false);
    else
        return syta.define_name (var, expression(), true);
}
double statement ()
{
    Token t = ts.get();
    switch (t.kind)
    {
        case let:
        case 'C':
            return declaration(t);
        default:
            ts.putback(t);
            return expression();
    }
}
void clean_up_mess ()
{
    ts.ignore (print);
}
void printHelp()
{
    cout << "Welcome to calculator by Alex Iachmenkov!\n You can use all things that we use in regular calculator;) \n If you want to use factorial write '!'\n If you want to use pow write (number)^(number) \n You can use common things like '+', '-', '*', '/', '%'  And you can use a lot of others things;) \n Use 'sqrt', 'sin', 'cos', 'tg', 'ctg', 'ln' \n Print 'exit' to exit the calculator \n";
}
void calculate ()
{
    syta.define_name ("pi", 3.141592653589793, true);
    syta.define_name ("e",  2.718281828459045, true);
    while (cin)
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit) return;
            if (t.kind == help[0]) {printHelp(); continue;};
            if (t.kind == showval[0]) {syta.print_values(); continue;}
            ts.putback(t);
            cout << result << statement() << endl;
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}