#include <iostream>

class vector
{
	int sz;
	double* elem;

public:

	vector(int s)	//Constructor
		: sz{ s }, elem{ new double[s] }
	{
		for (int i = 0; i < s; ++i)
			elem[i] = 0.0;
	}
	int size() const { return sz; }

	~vector()		//Destructor
	{
		delete[] elem;
	}

	double get(int n) const { return elem[n]; }		// get()

	void set(int n, double v) { elem[n] = v; }		//set()

};

int main()
{
	vector v(4);
	for (int i = 0; i < v.size(); ++i)
	{
		v.set(i, 1.1 * i);
		std::cout << "v[" << i << "]==" << v.get(i) << std::endl;
	}

	return 0;
}