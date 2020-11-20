#include "printHelp.h"
#include "tokenStream.h"
#include "keys.h"

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
  cin >> ch;

  switch (ch)
  {
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

      if (s == quitString) return Token{ quit};
      if (s == declkey) return Token{ let };
      if (s == sqrtString) return Token{ sqrtKey};
      if (s == powString) return Token{ powKey};
      if (s == logString) return Token { logKey };
      if (s == helpString) {
          printHelp();
          return Token{ help };
      }

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
