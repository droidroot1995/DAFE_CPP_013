#include "vector3.h"

template<typename T, typename A>
vector_base<T, A>::vector_base(const vector_base& arg) 
{
	T* p = alloc.allocate(arg.sz);
	for (int i = 0; i < arg.sz; ++i)
	{
		alloc.construct(&p[i], arg.elem[i]);
	}
	elem = p;
	sz = arg.sz;
	space = arg.space;
}

template<typename T, typename A>
vector_base<T, A>::vector_base(std::initializer_list<T> lst)
	:sz{ static_cast<int>(lst.size()) },
	elem{ alloc.allocate(sz) },
	space{ sz }
{
	std::copy(lst.begin(), lst.end(), elem);
}



template<typename T, typename A>
vector3<T, A>::vector3() 
	: vector_base<T, A>() {}

template<typename T, typename A>
vector3<T, A>::vector3(int s) 
	: vector_base<T, A>(s) 
{
	for (int i = 0; i < s; ++i) this->alloc.construct(&this->elem[i], T());
}

template<typename T, typename A>
vector3<T, A>::vector3(std::initializer_list<T> lst) 
	: vector_base<T, A>(lst) 
{
	std::copy(lst.begin(), lst.end(), this->elem);
}



template<typename T, typename A >
vector3<T, A>::vector3(const vector3<T, A>& arg)
	: vector_base<T, A>(arg) {}

template<typename T, typename A> 
vector3<T, A>& vector3<T, A>::operator=(const vector3<T, A>& a)
{
	if (this == &a)
	{
		return *this;
	}

	if (a.sz <= this->space)
	{
		for (int i = 0; i < a.sz; ++i)
		{
			this->elem[i] = a.elem[i];
		}
		this->sz = a.sz;
		return *this;
	}

	T* p = this->alloc.allocate(this->sz);
	for (int i = 0; i < a.sz; ++i)
	{
		p[i] = a.elem[i];
	}
	this->alloc.destroy(this->elem);
	this->space = this->sz = a.sz;
	this->elem = p;
	return *this;
}



template<typename T, typename A> 
vector3<T, A>::vector3(vector3<T, A>&& a)
{
	this->sz = a.sz;
	this->elem = a.elem;
	this->space = this->sz;
	a.sz = 0;
	a.elem = nullptr;
	a.space = a.sz;
}

template<typename T, typename A> 
vector3<T, A>& vector3<T, A>::operator=(vector3<T, A>&& a)
{
	this->alloc.destroy(this->elem);
	this->elem = a.elem;
	this->sz = a.sz;
	a.elem = nullptr;
	a.sz = 0;
	return *this;
}



template<typename T, typename A>
T& vector3<T, A>::at(int n)
{
	if (n <= 0 || this->sz > n) return this->elem[n];
	throw Range_error(n);
}

template<typename T, typename A> 
const T& vector3<T, A>::at(int n) const
{
	if (n <= 0 || this->sz > n) return this->elem[n];
	throw Range_error(n);
}



template<typename T, typename A> 
void vector3<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = this->sz; i < newsize; i++)
	{
		this->alloc.construct(&this->elem[i], val);
	}
	for (int i = 0; i < newsize; i++)
	{
		this->alloc.destroy(&this->elem[i]);
	}
	this->sz = newsize;
}

template<typename T, typename A> 
void vector3<T, A>::push_back(const T& val)
{
	if (!this->space)
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
	this->alloc.construct(&this->elem[this->sz], val);
	++this->sz;
}

template<typename T, typename A>
void vector3<T, A>::reserve(int newalloc) 
{
	if (newalloc <= this->space)
	{
		return;
	}
	vector_base<T, A> b(this->alloc, newalloc);
	std::uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
	for (int i = 0; i < this->sz; ++i)
	{
		this->alloc.destroy(&this->elem[i]);
	}
	std::swap<vector_base<T, A>>(*this, b);
}

template class vector3<int>;
template class vector3<double>;
template class vector3<char>;
template class vector3<std::string>;