//
//  token.hpp
//  Calculator 1.2
//
//  Created by Bogdan Bochkarev on 9/30/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>
#include <iostream>
#include "declare.hpp"
using namespace std;

double val;

//------------------------------------------------------------------------------

class Token {
    public:
        char kind;        // what kind of token
        double value;     // for numbers: a value
        string name;
        Token(char ch)    // make a Token from a char
            :kind(ch), value(0) { }
        Token(char ch, double val)     // make a Token from a char and a double
            :kind(ch), value(val) { }
        Token(char ch, string n)
            :kind(ch), name(n) { }
};

//------------------------------------------------------------------------------

class Token_stream {
    public:
        Token_stream();   // make a Token_stream that reads from cin
        Token get();      // get a Token (get() is defined elsewhere)
        void putback(Token t);    // put a Token back
        void ignore(char c);
    private:
        bool full {false};        // is there a Token in the buffer?
        Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------
// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream(): buffer {0} {}

//------------------------------------------------------------------------------
// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t){
    if (full) {
        throw runtime_error("ERROR: Buffer is full;");
    }
    buffer = t;
    full = true;
}

//------------------------------------------------------------------------------

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }
    char ch;
    cin >> ch;
    switch (ch) {
        case print:
        case quit:
        case '(': case ')': case '=':
        case '+': case '-': case '*':
        case '/': case '^': case '%':
        case '!': // all those symbols represent thmenselves
            return Token(ch);
        
        case '.': // float number can start with '.'
        // numeric literal
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            cin >> val;
            return Token(number, val);
        }
        default:
            if (isalpha(ch)) {
                string s;
                s += ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
                cin.putback(ch);
                if (s == declkey) return Token(let);
                else if (s == chankey) return Token(set);
                else if (s == sinkey) return Token{c_sin};
                else if (s == coskey) return Token{c_cos};
                else if (s == tankey || s == tankeyru) return Token(c_tan);
                else if (s == cotkey || s == cotkeyru) return Token(c_cot);
                else if (s == sqrtkey) return Token{square_root};
                else if (s == lnkey || s == logkey) return Token(c_ln);
                else if (s == exitkey) return Token(quit);
                return Token(name, s);
            }
            throw runtime_error("ERROR: Wrong token;");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c) {
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;
    
    char ch = 0;
    while (cin>>ch) if (ch == c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

#endif /* token_hpp */
