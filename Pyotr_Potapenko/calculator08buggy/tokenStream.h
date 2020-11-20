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


#endif // TOKENSTREAM_H
