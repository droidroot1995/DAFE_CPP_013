#include <iostream>
#include <algorithm>
#include <cstdlib>

struct Range_error :std::out_of_range
{
	int index;
	Range_error(int i) :std::out_of_range("Range error"), index{ i }{}
};

/*
template<typename T>
class allocator
{
	T* allocate(int n);
	void deallocate(T* p, int n);

	void construct(T* p, const T& v);
	void destroy(T* p);
};

template<typename T>
T* allocator<T>::allocate(int n)
{
	// c
	// return static_cast<T*>(malloc(sizeof (T) * n))

	// c++
	return reinterpret_cast<T*>(new char[sizeof(T) * n]);
}

template<typename T>
void allocator<T>::deallocate(T* p, int n)
{
	//c++
	delete[] reinterpret_cast<char*> (p);

	// c
	//free(p);
}

template<typename T>
void allocator<T>::construct(T* p, const T& v)
{
	//c++
	new(p) T(v);
}

template<typename T>
void allocator<T>::destroy(T* p)
{
	// c++
	p->~T();
}
*/

template<typename T, typename A>
struct vector_base
{
	A alloc;
	T* elem;
	int sz;
	int space;

	vector_base()
		: elem(alloc.allocate(0)), sz(0), space(0) {}

	vector_base(int n)
		: elem{ alloc.allocate(n) }, sz{ 0 }, space{ n } {}

	vector_base(const A& a, int n)
		: alloc{ a }, elem{ alloc.allocate(n) }, sz{ 0 }, space{ n } {}

	vector_base(const vector_base&);

	vector_base(std::initializer_list<T>);

	~vector_base() { alloc.deallocate(elem, space); }

};

template<typename T, typename A>
vector_base<T, A>::vector_base(const vector_base& a)
{
	T* p = alloc.allocate(a.sz);
	for (int i = 0; i < a.sz; ++i)
		alloc.construct(&p[i], a.elem[i]);
	elem = p;
	sz = a.sz;
	space = a.space;
}

template<typename T, typename A>
vector_base<T, A>::vector_base(std::initializer_list<T> lst)
	: sz{ int(lst.size()) }, elem{ new T[sz] }, space{ sz }
{
	std::copy(lst.begin(), lst.end(), elem);
}

template <typename T, typename A = std::allocator<T>>
class vector : private vector_base<T, A>
{

public:
	A alloc;
	int sz;		// Number of elements
	T* elem;	// Pointer to first element
	int space;	// sz + Extra slots

	vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } {};

	explicit vector(int s)					// initialisation
		: sz{ 0 }, elem{ nullptr }, space{ 0 }
	{
		resize(s);
	}
	vector(const std::initializer_list<T>& lst);

	vector(const vector&);					// Constructor copy
	vector& operator= (const vector&);		// Copy assignment

	vector(const vector&& a);				// Constructor move
	vector& operator= (const vector&&);		// Move assignment

	~vector() { delete[] elem; }			//Destructor

	T& at(int n);
	const T& at(int n) const;

	T& operator[] (int n);					// v[]
	const T& operator[] (int n) const;		// const v[]

	int size() const { return sz; }			// size()

	void reserve(int newalloc);				// vector::reserve()

	int capacity() const { return space; }	// capacity()

	void resize(int newsize);	// resize()

	void push_back(const T& val);			// push_back()
};

template<typename T, typename A>
vector<T, A>::vector(const std::initializer_list<T>& lst)
	: sz{ int(lst.size()) }, elem{ new T[sz] }
{
	std::copy(lst.begin(), lst.end(), elem);
}

template<typename T, typename A>
vector<T, A>::vector(const vector& arg)
	: sz{ arg.sz }, elem{ new T[arg.sz] }
{
	std::copy(arg.elem, arg.elem + sz, elem);
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (const vector& arg)
{
	if (&arg == this)
		return *this;
	if (arg.sz <= space)
	{
		for (int i = 0; i < arg.sz; ++i)
			elem[i] = arg.elem[i];
		sz = arg.sz;
		return *this;
	}
	T* buffer = new T[arg.sz];
	for (int i = 0; i < arg.sz; ++i)
		buffer[i] = arg.elem[i];
	delete[] elem;
	space = sz = arg.sz;
	elem = buffer;
	return *this;
}

template<typename T, typename A>
vector<T, A>::vector(const vector&& a)
	: sz{ a.sz }, elem{ a.elem }
{
	a.sz = 0;
	a.elem = nullptr;
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (const vector&& a)
{
	delete[] elem;
	elem = a.elem;
	sz = a.sz;
	a.elem = nullptr;
	a.sz = 0;
	return *this;
}

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= this->space)
		return;
	vector_base<T, A>
		b(this->alloc, newalloc);
	std::uninitialized_copy(elem, elem + sz, b.elem);
	b.sz = sz;
	for (int i = 0; i < this->sz; ++i)
		this->alloc.destroy(&this->elem[i]);
	this->alloc.deallocate(this->elem, this->space);
	//std::swap<vector_base<T, A>&>(static_cast<vector_base<T, A>&>(*this), b);
	this->elem = b.elem;
	this->sz = b.sz;
	this->space = b.space;
	b.elem = nullptr;
	b.sz = b.space = 0;
}

template<typename T, typename A>
void vector<T, A>::resize(int newsize)
{
	reserve(newsize);
	if (newsize < sz)
	{
		for (T* it = elem + newsize; it < elem + sz; ++it)
			alloc.destroy(it);
		sz = newsize;
	}
	else
	{
		T* i = elem + sz;
		try
		{
			for (int i = sz; i < elem + newsize; ++i)
				alloc.construct(i, T());
			sz = newsize;
		}
		catch (...)
		{
			for (T* it = elem + sz; it < i; ++it)
				alloc.destroy(it);
			throw;
		}
	}
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val)
{
	if (space == 0)
		reserve(8);
	else if (sz == space)
		reserve(2 * space);

	alloc.construct(elem + sz, val);
	++sz;
}

template<typename T, typename A>
T& vector<T, A>:: operator[](int n)
{
	return at(n);
}

template<typename T, typename A>
const T& vector<T, A>:: operator[](int n) const
{
	if (n < 0 || sz <= n)
		throw Range_error(n);
	return elem[n];
}

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
	if (n < 0 || sz <= n)
		throw Range_error(n);
	return elem[n];
}

int main()
{
	vector<int> vi;
	vi.push_back(55);
	vi.push_back(44);
	for (int i = 0; i < vi.size(); ++i)
		std::cout << vi[i] << ' ';

	std::cout << std::endl;

	vector<int> v = { 1, 2, 3, 4, 5, 6 };
	vector<int> v1 = { 10, 11, 12 };

	std::cout << "vector v1 : ";
	for (int i = 0; i < v1.size(); ++i)
		std::cout << v1[i] << ' ';
	std::cout << std::endl;

	std::cout << "vector v : ";
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';
	std::cout << std::endl;

	std::cout << "size v1: " << v1.size() << std::endl;
	std::cout << "size v: " << v.size() << std::endl;

	v = v1;

	std::cout << "vector v after v = v1: ";
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';
	std::cout << std::endl;

	v.push_back(5);
	std::cout << "vector v after v.push_back(5): ";
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';
	std::cout << std::endl;

	vector<std::string> vstr = { "I", "have", "done", "vector" };
	for (int i = 0; i < vstr.size(); ++i)
		std::cout << vstr[i] << ' ';

	std::cout << std::endl;

	std::cout << "space v: " << v.capacity() << std::endl;
	std::cout << "space v1: " << v1.capacity() << std::endl;
	return 0;
}