#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "std_lib_facilities.h"
#include "token.h"

class Token_stream
{
  bool full{ false };
  Token buffer{ '\0' };

public:
  Token_stream () { }

  Token get ();
  void putback (Token t);

  void ignore (char c);
};


void Token_stream::putback (Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char sqrtKey = 'S';
constexpr char powKey = 'P';

const string prompt = "> ";
const string result = "= ";
const string declkey = "#";
const string sqrtString = "sqrt";
const string powString = "pow";

Token Token_stream::get ()
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin >> ch;

  switch (ch)
  {
  case quit:
  case print:
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '=':
  case ',':
    return Token{ ch };

  case '.':
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
      while (cin.get(ch) &&
             (isalpha(ch) || isdigit(ch) || ch == '_'))
        s += ch;
      cin.putback(ch);

      if (s == declkey) return Token{ let };
      if (s == sqrtString) return Token{ sqrtKey};
      if (s == powString) return Token{ powKey};

      return Token{ name, s };
    } else {
        string s;
        s += ch;
        cout << s << endl;
        if (s == declkey) return Token{ let };
    }
    error("Bad token");
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

  char ch;
  while (cin >> ch)
    if (ch == c) return;
}


#endif // TOKENSTREAM_H
