#include "Variable.h"										// Подключение библиотеки для работы с переменными.


double get_value(string s)									// Описание функции, возвращающей
{															// значение переменной.
	for (const Variable& v : var_table)						//
	{														//
		if (v.name == s)									//
		{													//
			return v.value;									//
		}													//
	}														// В случае отсутствия данной переменной -
	error("get: undefined variable ", s);					// вызов ошибки
}															//
															
															
															
void set_value(string s, double d)							// Описание функции, изменяющей 
{															// значение переменной.
	for (Variable& v : var_table)							//
	{														//
		if (v.name == s)									//
		{													//
			if (v.cst)										//
			{												// В случае если переменная является константой -
				error("can not change value of a const");	// вызов ошибки.
			}												//
			v.value = d;									//
			return;											//
		}													//
	}														// В случае отсутствия данной переменной -
	error("set: undefined variable ", s);					// вызов ошибки.
}															//