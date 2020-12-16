#include <initializer_list>
#include <algorithm>


class vector1 {
	int sz;
	double* elem;
public:
	vector1(int);
	~vector1();
	int size();
	double get(int) const;
	void set(int, double);
};