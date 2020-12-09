#include "vector3.h"

template<typename T, typename A> vector_base<T, A>::vector_base(int s)
	:sz{ s },
	elem{ new T[s] },
	space{ s }
{
	for (int i = 0; i < s; ++i)
	{
		this->elem[i] = T();
	}
}

template<typename T, typename A> vector_base<T, A>::vector_base(std::initializer_list<T> lst)
	:sz{ static_cast<int>(lst.size()) },
	elem{ new T[this->sz] },
	space{ this->sz }
{
	std::copy(lst.begin(), lst.end(), this->elem);
}



template<typename T, typename A >vector3<T, A>::vector3(const vector3<T, A>& arg)
	:sz{ arg.sz },
	elem{ new T[arg.sz] }
{
	std::copy(arg.elem, arg.elem +sz, elem);
}

template<typename T, typename A> vector3<T, A>& vector3<T, A>::operator=(const vector3<T, A>& a)
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

	T* p = new T[a.this->sz];
	for (int i = 0; i < a.this->sz; ++i)
	{
		p[i] = a.this->elem[i];
	}
	delete[] this->elem;
	this->space = this->sz = a.this->sz;
	this->elem = p;
	return *this;
}



template<typename T, typename A> vector3<T, A>::vector3(vector3<T, A>&& a)
	:sz{ a.sz },
	elem{ a.elem }
{
	a.this->sz = 0;
	a.this->elem = nullptr;
}

template<typename T, typename A> vector3<T, A>& vector3<T, A>::operator=(vector3<T, A>&& a)
{
	delete[] this->elem;
	this->elem = a.this->elem;
	this->sz = a.this->sz;
	a.this->elem = nullptr;
	a.this->sz = 0;
	return *this;
}



template<typename T, typename A> T& vector3<T, A>::at(int n)
{
	if (n < 0 || this->sz <= n) throw Range_error(n);
	return this->elem[n];
}

template<typename T, typename A> const T& vector3<T, A>::at(int n) const
{
	if (n < 0 || this->sz <= n) throw Range_error(n);
	return this->elem[n];
}



template<typename T, typename A> void vector3<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = this->sz; i < newsize; i++)
	{
		alloc.construct(&this->elem[i], val);
	}
	for (int i = 0; i < newsize; i++)
	{
		alloc.destroy(&this->elem[i]);
	}
	this->sz = newsize;
}

template<typename T, typename A> void vector3<T, A>::push_back(const T& val)
{
	if (this->space == 0)
	{
		reserve(8);
	}
	else
	{
		if (this->sz == this->space)
		{
			reserve(2 * this->space);
		}
	}
	alloc.construct(&this->elem[this->sz], val);
	++this->sz;
}

template<typename T, typename A> 
void vector3<T, A>::reserve(int newalloc)
{
	if (newalloc <= this->this->space)
	{
		return;
	}
	vactor_base<T,A> b(this->alloc,newalloc);
	uninitialized_copy(b.this->elem, &Ü.this->elem[this->this->sz], this->this->elem);
	for (int i = 0; i < THIS->this->sz; ++i)
	{
		this->alloc.destroy(&this->this->elem[i]);
	}
	swap<vector_base<T, A>>(*this, b);
}

template class vector3<int>;
template class vector3<double>;
template class vector3<char>;
template class vector3<std::string>;