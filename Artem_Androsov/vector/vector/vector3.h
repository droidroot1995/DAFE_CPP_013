#include <initializer_list>
#include <string>
#include <algorithm>
#include <memory>
#include <stdexcept>

struct Range_error : std::out_of_range {
	int index;
	Range_error(int i) : std::out_of_range("Range error"), index{ i } {};
};

//template<typename T> struct Vector :public std : vector<T>
//{
//	using size_type = typename std::vector<T>::size_type;
//	using vector<T>::vector;
//	
//	T& operator[](size_type i)
//	{
//		if (i < 0 || this->size() <= i)
//		{
//			throw Range_error(i);
//		}
//		return std::vector<T>::operator[](i);
//	}
//
//	const T& operator[](size_type i) const
//	{
//		if (i < 0 || this->size() <= i)
//		{
//			throw Range_error(i);
//		}
//		return std::vector<T>::operator;
//	}
//
//};

template<typename T, typename A> struct vector_base
{
	A alloc;
	T* elem;
	int sz;
	int space;

	vector_base() :sz{ 0 }, elem{ alloc.allocate(0) }, space{ 0 } {}
	vector_base(int n) : elem(alloc.allocate(n)), sz(n), space(n) {}
	vector_base(const A& a, int n) :alloc{a}, elem{ alloc.allocate(n) }, sz{ n }, space{ n } {}
	vector_base(const vector_base& arg);
	vector_base(std::initializer_list<T> lst);
	~vector_base() { alloc.deallocate(elem, space); }
};

template<typename T, typename A = std::allocator<T>> 
class vector3 : private vector_base<T,A>
{
public:
	vector3();
	vector3(int);
	vector3(std::initializer_list<T> lst);

	vector3(const vector3& arg);
	vector3& operator=(const vector3& a);

	vector3(vector3&& a);
	vector3& operator=(vector3&& a);

	~vector3() {}

	T& at(int n);
	const T& at(int n) const;

	T& operator[] (int n) { return this->elem[n]; }
	const T& operator[] (int n) const { return this->elem[n]; }

	int capacity() const { return this->space; }
	int size() const { return this->sz; };

	void resize(int newsize, T val = T());
	void push_back(const T& val);
	void reserve(int newalloc);
};