#include <iostream>
#include <algorithm>

struct Range_error :std::out_of_range
{
	int index;
	Range_error(int i) :std::out_of_range("Range error"), index{ i }{}
};

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
		: elem{ alloc.allocate(n) }, sz{ n }, space{ n } {}

	vector_base(const A& a, int n)
		: alloc{ a }, elem{ alloc.allocate(n) }, sz{ n }, space{ n } {}

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
		: sz{ s }, elem{ new T[s] }, space{ s }
	{
		for (int i = 0; i < sz; ++i)
			elem[i] = 0;
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

	void resize(int newsize, T val = T());	// resize()

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
	std::uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
	for (int i = 0; i < this->sz; ++i)
		this->alloc.destroy(&this->elem[i]);
	std::swap<vector_base<T, A>>(*this, b);
}

template<typename T, typename A>
void vector<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i)
		alloc.construct(&elem[i], val);
	for (int i = newsize; i < sz; ++i)
		alloc.destroy(&elem[i]);
	sz = newsize;
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val)
{
	if (space == 0)
		reserve(8);
	else if (sz == space)
		reserve(2 * space);
	alloc.construct(&elem[sz], val);
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
	vector<int> v = { 1, 2, 3, 4, 5, 6 };
	for (int i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';
	return 0;
}