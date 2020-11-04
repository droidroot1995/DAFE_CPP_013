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

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char sqrtKey = 'S';
constexpr char powKey = 'P';
constexpr char help = 'h';
constexpr char logKey = 'l';

const string prompt = "> ";
const string result = "= ";
const string declkey = "#";
const string sqrtString = "sqrt";
const string powString = "pow";
const string logString = "log";
const string quitString = "quit";
const string helpString = "help";


#endif // TOKENSTREAM_H
