#pragma once
#include <iostream>
#include "std_lib_facilities.h"
using namespace std;

class Token
{
public:
	char kind;
	double value;
};

class Token_stream
{
public:
	Token get();
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;
};