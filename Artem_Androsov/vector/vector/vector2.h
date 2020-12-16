#include <initializer_list>
#include <algorithm>

class vector2
{
	int sz;
	double* elem;

public:

	vector2(int s);
	vector2(std::initializer_list<double> lst);

	vector2(const vector2& arg);
	vector2& operator=(const vector2& a);

	vector2(vector2&& a);
	vector2& operator=(vector2&& a);

	~vector2(){delete[] elem;}

	double& operator[] (int n){return elem[n];}
	double operator[] (int n) const { return elem[n]; }

	int size() const { return sz; };
	double get(int n) const { return elem[n]; }
	void set(int n, double v) { elem[n] = v; }
};