#pragma once
#include "Variable.h"									// ѕодключение вайла дл€ работы с со всеми объ€вленными классами и функци€ми.

void calculate();
double statement();										// ‘ункци€ дл€ обработки поданной последовательности символов.
double declaration();									// ‘ункци€ дл€ создани€ новой переменной
double sett();											// ‘ункци€, измен€юща€ значение переменной.

bool is_declared(string var);							// ‘ункци€ провер€юща€, существует ли уже така€ переменна€.
double define_name(string var, double val, bool c);		// ‘ункци€, выполн€ющаа€ определение переменной.

