#include <iostream>

// Add to class vector:
// Create objects of type double
// Copy objects with assignment and initialization 
// Any quanity of elements
// Safe memory used and clean
// Use [] to access to element

class vector
{
	int sz; // Number of elements
	double* elem; // Pointer to first element

public:

	explicit vector(int s);									// Constructor 
	vector(const std::initializer_list<double>& lst);		// initialization list

	~vector()		//Destructor
	{
		delete[] elem;
	}


	vector(const vector&);		// Constructor copy
	vector& operator= (const vector&);	// Copy assignment

	vector(vector&& a);			// Constructor move
	vector& operator= (vector&&); // Move assignment

	int size() const { return sz; }					// size()

	double& operator[] (int n) { return elem[n]; }			// v[]

	double& operator[] (int n) const { return elem[n]; }	// const v[]
};

vector::vector(int s)
	: sz{ s }, elem{ new double[s] }
{
	for (int i = 0; i < s; ++i)
		elem[i] = 0;
}

vector::vector(const std::initializer_list<double>& lst)
	: sz{ int(lst.size()) }, elem{ new double[sz] }
{
	std::copy(lst.begin(), lst.end(), elem);
}

vector::vector(const vector& arg)
	: sz{ arg.sz }, elem{ new double[arg.sz] }
{
	std::copy(arg.elem, arg.elem + sz, elem);
}

vector& vector::operator= (const vector& arg)
{
	if (&arg == this)
		return *this;

	double* buffer = new double[arg.sz];
	std::copy(arg.elem, arg.elem + arg.sz, buffer);
	delete[] elem;
	elem = buffer;
	sz = arg.sz;
	return *this;
}

vector::vector(vector&& a)
	: sz{ a.sz }, elem{ a.elem }
{
	a.sz = 0;
	a.elem = nullptr;
}

vector& vector::operator= (vector&& a)
{
	delete[] elem;
	elem = a.elem;
	sz = a.sz;
	a.elem = nullptr;
	a.sz = 0;
	return *this;
}

int main()
{
	vector v0 = { 1.1, 4.5, 6,9 };

	for (int i = 0; i < v0.size(); ++i)
		std::cout << v0[i] << " ";
	std::cout << std::endl;
	vector v(10);

	for (int i = 0; i < v.size(); ++i)
		v[i] = i;

	vector v2 = v;
//	for (int i = 0; i < v2.size(); ++i)
//		std::cout << v2[i] << ' ';

	v[3] = v2[1];

	int size = v.size();

	return 0;
}