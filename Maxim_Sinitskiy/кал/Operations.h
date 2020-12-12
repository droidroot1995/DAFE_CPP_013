#pragma once
#include "Token.h"


double primary(Token_stream &ts);


double term(Token_stream &ts);


double expression(Token_stream &ts);