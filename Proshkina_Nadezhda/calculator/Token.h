#ifndef TOKEN_H
#define TOKEN_H
#include "std_lib_facilities.h"

const double pi = 3.141592653589793;
const double e = 2.718281828459045;


constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char enter = '\n';
constexpr char konst = 'k';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string constkey = "const";
const string quitkey = "quit";




struct Token
{
  char kind;
  double value;
  string name;

  Token (char ch)
    : kind{ ch }
  { }

  Token (char ch, double val)
    : kind{ ch }, value{ val }
  { }

  Token (char ch, string n)
      : kind{ ch }, name{ n }
  { }
};


class Token_stream
{
public:
  Token_stream () : in{ cin } { }
  Token_stream (istream& s) : in{s} {}

  Token get();

  void putback (Token t);
  void ignore (char);

private:
  istream& in;
  bool full{false};
  Token buffer{'\0'};
};

void clean_up_mess(Token_stream& ts);

#endif
