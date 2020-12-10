#include "vector1.h"

vector1::vector1(int s) : sz{ s }, elem{ new double[s] } {
	for (int i = 0; i < s; ++i)
		elem[i] = 0;
}
vector1::~vector1() { delete[] elem; }
int vector1::size() { return sz; }
double vector1::get(int n) const { return elem[n]; }
void vector1::set(int n, double v) { elem[n] = v; }