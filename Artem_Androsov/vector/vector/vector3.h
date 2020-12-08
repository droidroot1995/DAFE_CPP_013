#include <initializer_list>
#include <algorithm>

class vector3
{
	int sz;
	double* elem;
	int space;

public:

	vector3() :sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	vector3(int s);
	vector3(std::initializer_list<double> lst);

	vector3(const vector3& arg);
	vector3& operator=(const vector3& a);

	vector3(vector3&& a);
	vector3& operator=(vector3&& a);

	~vector3() { delete[] elem; }

	double& operator[] (int n) { return elem[n]; }
	const double operator[] (int n) const { return elem[n]; }

	int capacity() const { return space; }
	int size() const { return sz; };

	void resize(int newsize);
	void push_back(double d);
	void reserve(int newalloc);
};