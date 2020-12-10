#include <initializer_list>
#include <algorithm>


class vector2 {
	int sz;
	double* elem;
public:
	vector2(int);
	vector2(const vector2&);
	vector2(std::initializer_list<double>);
	vector2(vector2&&);
	vector2& operator=(const vector2&);
	vector2& operator=(vector2&&);
	double operator[](int) const;
	double& operator[](int);

	~vector2();
	int size();
	double get(int) const;
	void set(int, double);
};
