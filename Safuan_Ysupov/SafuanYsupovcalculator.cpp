//Ysupov Safuan 17.10.20  
/*
Простой калькулятор

История версий:

Переработана Юсуповым Сафуаном в октябре 2020 (09.10.20)
Переработан Бьярне Страуструпом в мае 2007 г.
Переработан Бьярне Страуструпом в августе 2006 г.
Переработан Бьярне Страуструпом в августе 2004 г.
Разработан Бьярне Страуструпом (bs@cs.tamu.edu) весной 2004 г.

Эта программа реализует основные выражения калькулятора.
Ввод осуществляется из потока cin ; вывод - в поток cou t.

Грамма тика для ввода :

Инструкция:
  Выражение
  Вывод
  Выход

Вывод:
    ;
Выход:
    q

Выражение:
  Терм
  Выражение + Терм
  Выражение - Терм

Терм:
  Первичное_выражение
  Терм * Первичное_выражение
  Терм / Первичное_выражение
  Терм % Первичное_ выражение

Первичное_выражение :
  Число
  ( Выражение )
  - Первичное_выражение
  + Первичное_выражение

Число :
  Литерал_с_плавающей_точкой

Ввод из потока cin через Token stream с именем ts.
*/
#include "std_lib_facilities.h"
#include <iostream>
using namespace std;



const char number = '8'; // t.kind==number означает, что t - число
const char quit = 'q';  //  t.kind==quit означает, что t - лексема выхода
const char print = ';'; // t.kind==print означает, что t - лексема печати 
const string prompt = "> "; // Используется для указания на то,
const string result = "= "; // что далее следует результат
const char name = 'a';
const char let = 'L';
const string declkey = "let";

class Token
{
public:
    char kind;
    double value;
    string name;
    // Инициализирует kind символом ch
    Token(char ch) : kind{ ch } {}
    // Инициализирует kind и value
    Token(char ch, string n) : kind{ ch }, name{ n }  { }
    // Инициализирует kind и name
    Token(char ch, double val) : kind{ ch }, value{ val }  { }
};


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

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get() //Чтение из cin и составление Token 
{
    if (full)         // do we already have a Token ready?
    {
        full = false;   // remove Token from buffer
        return buffer;
    }

    char ch;
    cin >> ch;  // note that >> skips whitespace (space, newline, tab, ...)

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
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token{ number, val };  // let '8' represent "a number"
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while ((cin.get(ch)) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);
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
    while (cin >> ch)
        if (ch = c) return;
}


class Variable
{
public:
    string name;
    double value;

    Variable(string n, double v):
        name{ n }, value{ v } {}
    double get_value(string s);
    void set_value(string s, double d);
};

vector<Variable> var_table;


double get_value(string s)
//Возвращает значение переменной с именем s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
// Присваивает объекту s типа Variable значение d
{
    for (Variable& v : var_table)
        if (v.name == s)
        {
            v.value = d;
            return;
        }
    error("set: неопределённая переменная ", s);
}

bool is_declared(string var)
//Есть ли переменная var в векторе var_table?
{
    for (const Variable v : var_table)
        if (v.name == var)
            return true;
    return false;
}

double define_name(string var, double val)
// Добавляем пару (var,val) в вектор var_table
{
    if (is_declared(var)) error(var, " повторное объявление11 ");
    var_table.push_back(Variable{ var, val });
    return val;
}

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
    while (cin)
    try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get(); // Отбрасывание команд вывода
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << '\n';
    }
    catch (exception& e)
    {
        cerr << e.what() << '\n'; // Вывод сообщения об ошибке
        clean_up_mess();
    }
}

int main()
try
{
    setlocale(LC_ALL, "Russian");
    //Предопределённые имена
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    calculate();

    //keep_window_open(); // Удерживает консольное окно открытым
    return 0;
}
catch (runtime_error& e)   //exception
{
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}

catch (...)
{
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}