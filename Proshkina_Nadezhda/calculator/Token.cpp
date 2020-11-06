#include "Token.h"

void Token_stream::putback (Token t)
{
    if (full)
            error("putback() into a full buffer");
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
  do{cin.get(ch);}

  while (isspace(ch)&&ch != '\n');
  if (!cin)
      error("End of input stream");

  switch (ch)
  {
  case quit:
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case ';':
  case '=':
  case '^':
    return Token{ ch };

  case enter:
      return Token{print};


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
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
        s += ch;
      cin.putback(ch);

      if (s == declkey) return Token{ let };
      if (s == constkey) return Token{konst};
      if (s == quitkey) return Token{quit};
      else
        return Token{name, s};
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

  char ch = '\0';
  while (in.get(ch))
    if (ch == c || ch == '\n') return;
};

void clean_up_mess(Token_stream& ts)
{
   ts.ignore(print);
}
