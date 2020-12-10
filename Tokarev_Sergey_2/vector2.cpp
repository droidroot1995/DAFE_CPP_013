#include "vector2.h"

//size constructor
vector2::vector2(int s) : sz{ s }, elem{ new double[s] } {
	for (int i = 0; i < s; ++i)
		elem[i] = 0;
}
//init
vector2::vector2(std::initializer_list<double> lst) : sz(lst.size()), elem{ new double[sz] } {
	std::copy(lst.begin(), lst.end(), elem);
}
//copy copyconstructor
vector2::vector2(const vector2& arg) : sz{ arg.sz }, elem{ new double[arg.sz] } {
	std::copy(arg.elem, arg.elem + arg.sz, elem);
}
//move construtor
vector2::vector2(vector2&& a) : sz{ a.sz }, elem{ a.elem } {
	a.sz = 0;
	a.elem = nullptr;
}
//distructor
vector2::~vector2() { delete[] elem; }

//overloaded operators
double vector2::operator[](int n) const { return elem[n]; }
double& vector2::operator[](int n) { return elem[n]; }
vector2& vector2::operator=(const vector2& a) {
	double* p = new double[a.sz];
	std::copy(a.elem, a.elem + a.sz, p);
	delete[] elem;
	elem = p;
	sz = a.sz;
	return *this;
}
//move operator=
vector2& vector2::operator=(vector2&& a) {
	delete[] elem;
	elem = a.elem;
	sz = a.sz;
	a.elem = nullptr;
	a.sz = 0;
	return *this;
}

//other
int vector2::size() { return sz; }
double vector2::get(int n) const { return elem[n]; }
void vector2::set(int n, double v) { elem[n] = v; }



