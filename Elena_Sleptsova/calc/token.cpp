#include "token.h"
#include "std_lib_facilities.h"

Token_stream :: operator bool() const{}

void Token_stream :: putback (Token t)
{
	if (full == true)
		error("putback(): буфер заполнен")
	else
	{
		buffer = t;
		full = true;
	}
}

Token Token_stream :: get 
{
	if (full == true)
	{
		full = false;
		return buffer;
	}
	else
	
	}

void Token_stream ::ignore (char c) {}

