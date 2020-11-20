#include "Token.h"																// ����������� ������ ����� ��� ������ � ���. 


void Token_stream::putback(Token t)												// �������� �������, ������������ ����� ������� � �����.
{																				//
	if (full)																	// ���� ����� ����� -
	{																			//
		error("putback(): buffer is full");										// ����� ������.
	}																			//
	buffer = t;																	// ������ � �����,
	full = true;																// ����������� ������ �����������.
}



void Token_stream::ignore(char c)												// �������� �������, ������������ ������ �� ������������ �������.
{																				//
	if (full && c == buffer.kind)												// ���� ����� �������� �������� �������� - 
	{																			//
		full = false;															// ������� ������,
		return;																	// ��������� �������.
	}																			//
	full = false;																// ������� ������.
	char ch = 0;																//
	while (cin >> ch)															// ��������� �������,
	{																			//  
		if (ch == c)															// ���� �� ����� ��������� �������� ������.
		{																		//
			return;																//
		}																		//
	}																			//
}																				



Token Token_stream::get()														// �������� �������, ������� ��������� �������� �� ������.
{																				//
	if (full)																	// ���� ����� ����� -
	{																			//
		full = false;															// 
		return buffer;															// ���������� ����� �� ������.
	}																			//
	char ch;																	// ������ ���������� �������� 
	cin >> ch;																	// �� ������ cin.
																				//
	switch (ch)																	// ����� ��������� � ����������� �� ������������� ����� ��������
	{																			//
	case ';':																	// � ���� �������
	case '(': case ')':															// � �������� ������ ������������
	case '+': case '-':															// ������ � �����, ����������
	case '*': case '/':															// ����� ��������.
	case '%': case '=':															//
	case '@': case '!':															//
		return Token{ ch };														// ������� ������ ������.
	case '#':																	//
		return Token{ let };													// ������� ������, ������������� ����������������� ����� ��� ���������� ����������.
	case '&':																	//
		return Token{ set };													// ������� ������, ������������� ����������������� ����� ��� ��������� �������� ����������.
																				//
	case '.':																	// � ������ ������� ����� ��� ����� -
	case '0': case '1': case '2': case '3': case '4':							// ���������� �����, ������������ �����.
	case '5': case '6': case '7': case '8': case '9':							//
	{																			//
		cin.putback(ch);														// ������� ����� ��� ���������� ������� �����.
		double val;																//
		cin >> val;																// ���������� ��������.
		return Token{ number,val };												// ������� ������-�����.
	}																			//
	default:																	// �� ���� ��������� ������� ����� ��������� �����, 
		if (isalpha(ch))														// ����� ������ �� �������� �� ��� ����� ���� 
		{																		// ����������������� ������.
			string s;															//
			s += ch;															//
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))	// ���������� �����.
			{																	//
				s += ch;														//
			}																	//
			cin.putback(ch);													//
			return Token{ name,s };												// ������� ������, ��������������� �����.
		}																		//
		error("wrong token");													// � ������ ����������� �������� �������� - ������������� ������.
	}																			//
}																				//