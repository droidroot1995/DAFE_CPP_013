#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"

const char number = '8'; // t.kind==number means that t is a number
const char quit = 'q';
const string quitF = "exit";  //  t.kind==quit означает, means that t is the exit token
const char print = ';'; // t.kind==print means that t is the print token
const string prompt = "> "; // Used to indicate that,
const string result = "= "; // what follows is the result
const char name = 'a';

const char let = 'L';
const string declkey = "let";

const string help = "help";     // To open the help window

const char pow_ = 'p';
const string pow_key = "pow"; // For exponentiation

const char log10_ = 'l';
const string log_key = "log10";  // to calculate the decimal logarithm

const char sqrt_ = 's';
const string sqrt_key = "sqrt"; // to calculate the square root

class Token_stream
{
public:
    Token get();            // Reads the token
    void putback(Token t);  // Returns the token to the stream
    void ignore(char c);    // Discards characters up to
    Token_stream() {};      // up to and including the symbol
private:
    bool full{ false };  // is there a Token in the buffer?
    Token buffer{ '\0' };        // here we keep a Token put back using putback()

};

#endif
