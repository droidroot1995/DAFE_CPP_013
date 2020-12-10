#include "vectorChapter17.h"

vector:: vector (int s) // Конструктор
    : sz{s},  elem { new double[s]} // Выделение памяти
{
    for (int i = 0; i<s; ++i)
        elem[i] = 0;
}
