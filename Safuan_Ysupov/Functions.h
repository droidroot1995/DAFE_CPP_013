#include "std_lib_facilities.h"
#include <iostream>
#include "Token_stream.h"
#include "factorial.h"

Token_stream ts;        // provides get() and putback()
double expression();    // ad for use in primary()

/// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':          // handle '(' expression ')' 
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}')
            error("need '}' ");
        return d;
    }
    case '|':                       // module
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '|')
            error("'|' expected");
        return abs(d);
    }
    case number:          // we use '8' to represent a number
        return t.value;
    case name:
        return get_value(t.name);
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
    {
        ts.putback(t);
        error("primary expected");
    }
    }
}

//the secondary expression is needed to calculate the factorial so that it can work without parentheses
double secondary()               
{
    double left = primary();
    Token t = ts.get();
    switch (t.kind)
    {
    case '!':
    {
        if (fmod(left, 1) != 0) error("for factorial you need integer");
        left = factorial(left);
        t = ts.get();
        break;
    }
    default:
        ts.putback(t);
    }
    return left;
}

// For a tertiary expression that performs actions with elements in parentheses.
// Decimal logarithm, power, square root
double third() 
{
    Token t = ts.get();
    switch (t.kind)
    {
    case pow_:
    {
        t = ts.get();
        if (t.kind != '(') error("you need '('");
        double left = expression();
        t = ts.get();
        if (t.kind != ',') error("you need ','");
        double right = expression();
        if (fmod(right, 1) != 0) error("for pow need integer"); //fmod - fractional part when divided by 1
        t = ts.get();
        if (t.kind != ')') error("you need ')'");
        return pow(left, right);
    }
    case sqrt_:
    {
        t = ts.get();
        if (t.kind != '(') error("for sqrt need '('");
        double d = expression();
        if (d < 0) error("sqrt of less than 0");
        d = sqrt(d);
        t = ts.get();
        if (t.kind != ')') error("sqrt need ')'");
        return d;
    }
    case log10_:
    {
        t = ts.get();
        if (t.kind != '(') error("for log10 need '('");
        double d = expression();
        if (d < 0) error("in log10 can't be negative");
        d = log10(d);
        t = ts.get();
        if (t.kind != ')') error(" for log10 need ')'");
        return d;
    }
    default:
        ts.putback(t);
        return secondary();
    }
}
/// deal with *, /, and %
double term()
{
    double left = third();
    Token t = ts.get();    // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= third();
            t = ts.get();
            break;
        case '/':
        {
            double d = third();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        //You can also disable the % operation for floating-point arguments (the second option is case)
        case '%':                                       //int i1=narrow_cast<ini>(left);
        {                                               //int i2=narrow_cast<ini>(primary());
            double d = third();                       //if (i2==0) error("%: division by zero"); 
            if (d == 0) error("%: division by zero");   //left=i1%i2;
            left = fmod(left, d);                       //t=ts.get();
            t = ts.get();
            break;                                      //break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

/// deal with + and -
double expression()
{
    double left = term();  // read and evaluate a Term
    Token t = ts.get();    // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;

        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;

        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration()
// We believe that we have already encountered the word "let"
// Processing: Name = Expression
// Declaration of a variable with A name with an initial value,
// specified by the Expression
{
    Token t = ts.get();
    if (t.kind != name)
        error("The variable name is expected in the Declaration");
    string var_name = t.name;
    Token t2 = ts.get();
    if (t2.kind != '=')
        error("Пропущени символ '=' в объявлении", var_name);
    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return  declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess() 
{
    ts.ignore(print);
}

void calculate() //Cycle for computing the expression
{
    string iname = "D:/Progs/DAFE_CPP_013/Safuan_Ysupov/calc_cin.txt";
    ifstream ist{ iname };
    if (!ist)
        error("can't open file", iname);
    string oname = "D:/Progs/DAFE_CPP_013/Safuan_Ysupov/calc_cout.txt";
    ofstream ost{ oname };
    if (!ost)
        error("can't open file", oname);
    while (ist)
        try
    {
        ost << prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get(); // Discarding output commands
        if (t.kind == quit) return;
        ts.putback(t);
        ost << result << statement() << '\n';
    }
    catch (exception& e)
    {
        ost << e.what() << '\n'; // The output of the error message
        clean_up_mess();
    }
}

