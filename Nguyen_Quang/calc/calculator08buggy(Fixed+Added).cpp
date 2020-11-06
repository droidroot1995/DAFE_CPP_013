/*
  calculator08buggy.cpp

  Helpful comments removed.

  We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"


struct Token
{
  char kind;
  double value;
  string name;

  Token (char ch)
    : kind{ ch }, value{ 0 }
  { }

  Token (char ch, double val)
    : kind{ ch }, value{ val }
  { }

  Token (char ch, string n) //added this Token 
    : kind{ch} , name {n}
  { }  

};


class Token_stream
{
  bool full{ false };
  Token buffer{ '\0' };

public:
  Token_stream () { }

  Token get ();
  void putback (Token t);

  void ignore (char c); // added "c"
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
constexpr char sqrts = 's'; //added this line (indicates square root)
constexpr char pows = 'p'; // added this line

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string sqrtString = "sqrt";//added
const string powString = "pow";//added
const string exitString ="quit";//added


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
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case ';':
  case '=':
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
             (isalpha(ch) || isdigit(ch)))
        s += ch; // added "+"
      cin.putback(ch);

      if (s == declkey) return Token{ let };
      if (s == sqrtString ) return Token{sqrts}; //added 1
      if (s == powString ) return Token{pows}; // 2
      if (s == exitString ) return Token{quit}; // 3

      return Token{ name, s };
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


struct Variable
{
  string name;
  double value;

  Variable (string n, double v)
    : name{ n }, value{ v }
  { }
};

vector<Variable> var_table;

double get_value (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: undefined name ", s);
}

void set_value (string s, double d)
{
  for (int i = 0; i <= var_table.size(); ++i)
  {
    if (var_table[i].name == s)
    {
      var_table[i].value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool is_declared (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s) return true;
  return false;
}

double define_name (string var, double val)
{
  if (is_declared(var))
    error(var, " declared twice");

  var_table.push_back (Variable{ var, val });

  return val;
}


Token_stream ts;

double expression ();

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
      error("')' expected"); //fixed "(" -> ")"
    return d;
  }

  case sqrts: // added "sqrts" case
  {
    double d = primary();
    if(d<0)
      error ("square root of negative number was detected");
    return sqrt(d);  
  }

  case pows: // added "pows" case
  {
    t = ts.get();
    if(t.kind == '('){
      double lval = primary();
      int rval = 0;
      t = ts.get();
      if(t.kind==',') rval = narrow_cast<int>(primary());
      else error("Second argument is not provided");
      double result = 1;
      for (double i = 0;i<rval;i++){
        result*=lval;
      }
      t = ts.get();
      if(t.kind != ')') error("')' expected");
      return result;
    }
    else error("'(' expected");
    
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


double term ()
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
      if (d == 0) error("divide by zero");
      left /= d;
      break;
    }

    case '!': //added "factorial" case
    {
      int x = left;
      for (int i = 1;i < left;i++){
        x*=i;
      }
      if (x == 0) left = 1;
      else left = x;
      break;
    }

    case '%': //added "module"
    {
      double d = primary();
      if(d == 0) error("division by zero");
      left = fmod(left,d);
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


double declaration ()
{
  Token t = ts.get();
  if (t.kind != name)
    error("name expected in declaration");

  string var = t.name;
  if (is_declared(var))
    error(var, " declared twice");

  Token t = ts.get(); //added "Token"
  if (t.kind != '=')
    error("'=' missing in declaration of ", var);

  return define_name (var, expression());
}


double statement ()
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


void clean_up_mess ()
{
  ts.ignore (print);
}


void calculate ()
{
  while (true)
  try
  {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print)
      t = ts.get();
    if (t.kind == quit) return;

    ts.putback(t);
    cout << result << statement() << endl;
  }
  catch (runtime_error& e)
  {
    cerr << e.what() << endl;
    clean_up_mess();
  }
}


int main ()
try
{
  define_name ("pi", 3.141592653589793);
  define_name ("e",  2.718281828459045);

  calculate();
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  char c; //added 1
  while(cin >> c&&c!=';');//2
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  char c; //added 1
  while (cin >> c&&c!=';');//2
  return 2;
}
