#include "Token.h"

void Token_stream::putback(Token t)
{
	if (full)
	{
		error("putback(): buffer is full");
	}
	buffer = t;
	full = true;
}

Token Token_stream::get()
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
	case ';':
	case 'q':
	case '(': case ')': case '+':
	case '-': case '*': case '/':
		return Token{ ch };
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ '8',val };
	}
	default:
		error("wrong token");
	}
}