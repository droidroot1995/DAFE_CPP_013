#include "vector3.h"

vector3::vector3(int s) 
	:sz{ s }, 
	elem{ new double[s] }, 
	space{ s }
{
	for (int i = 0; i < s; ++i)
	{
		elem[i] = 0;
	}
}

vector3::vector3(std::initializer_list<double> lst)
	:sz{ static_cast<int>(lst.size()) },
	elem{ new double[static_cast<int>(lst.size())] },
	space{ static_cast<int>(lst.size()) }
{
	std::copy(lst.begin(), lst.end(), elem);
}



vector3::vector3(const vector3& arg)
	:sz{ arg.sz },
	elem{ new double[arg.sz] }
{
	std::copy(arg.elem, arg.elem + sz, elem);
}

vector3& vector3::operator=(const vector3& a)
{
	if (this == &a)
	{
		return *this;
	}

	if (a.sz <= space)
	{
		for (int i = 0; i < a.sz; ++i)
		{
			elem[i] = a.elem[i];
		}
		sz = a.sz;
		return *this;
	}

	double* p = new double[a.sz];
	for (int i = 0; i < a.sz; ++i)
	{
		p[i] = a.elem[i];
	}
	delete[] elem;
	space = sz = a.sz;
	elem = p;
	return *this;
}



vector3::vector3(vector3&& a)
	:sz{ a.sz },
	elem{ a.elem }
{
	a.sz = 0;
	a.elem = nullptr;
}

vector3& vector3::operator=(vector3&& a)
{
	delete[] elem;
	elem = a.elem;
	sz = a.sz;
	a.elem = nullptr;
	a.sz = 0;
	return *this;
}



void vector3::resize(int newsize)
{
	reserve(newsize);
	for (int i = sz; i < newsize; i++)
	{
		elem[i] = 0;
		sz = newsize;
	}
}

void vector3::push_back(double d)
{
	if (space == 0)
	{
		reserve(8);
	}
	else
	{
		if (sz == space)
		{
			reserve(2 * space);
		}
	}
	elem[sz] = d;
	++sz;
}

void vector3::reserve(int newalloc)
{
	if (newalloc <= space)
	{
		return;
	}
	double* p = new double[newalloc];
	for (int i = 0; i < sz; ++i)
	{
		p[i] = elem[i];
	}
	delete[] elem;
	elem = p;
	space = newalloc;
}