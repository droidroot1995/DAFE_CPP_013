#include "std_lib_facilities.h"
#include <iostream>
#include "Token_stream.h"

Token_stream ts;        // предоставляет get() и putback()
double expression();    // объявление для использования в primary()

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
        {
            error("need '}' ");
        }
        return d;
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
        error("primary expected");
    }
}

/// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();    // get the next token from token stream

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        //Можно и так, чтобы запретить операцию % для аргументов с плавающей точкой (второй вариант case)
        case '%':                                       //int i1=narrow_cast<ini>(left);
        {                                               //int i2=narrow_cast<ini>(primary());
            double d = primary();                       //if (i2==0) error("%: division by zero"); 
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
// Считаем, что мы уже встретили слово "let"
// Обрабатываем: Имя=Выражение
// Объявление переменной с Именем с начальным значением,
// заданным Выражением
{
    Token t = ts.get();
    if (t.kind != name)
        error("В объявлении ожидается имя переменной");
    string var_name = t.name;
    Token t2 = ts.get();
    if (t2.kind != '=')
        error("Пропущени символ = в объявлении", var_name);
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

void clean_up_mess() // наивное решение
{
    ts.ignore(print);
}

void calculate() //Цикл для вычислений выражения
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
            t = ts.get(); // Отбрасывание команд вывода
        if (t.kind == quit) return;
        ts.putback(t);
        ost << result << statement() << '\n';
    }
    catch (exception& e)
    {
        ost << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();
    }
}

