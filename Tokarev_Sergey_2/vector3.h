#include <initializer_list>
#include <algorithm>


template<typename T> class vector3 {
	int sz;
	T* elem;
	int space;
public:
	vector3() : sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	explicit vector3(int s) : sz{ s }, elem{ new T[s] }, space{ s } {
		for (int i = 0; i < sz; ++i)
			elem[i] = 0;
	}
	//copy constructor
	vector3(const vector3& arg) : sz{ arg.sz }, elem{ new T[arg.sz] } {
		std::copy(arg.elem, arg.elem + arg.sz, elem);
	}
	//move constructor
	vector3(vector3&& a) : sz{ a.sz }, elem{ a.elem } {
		a.sz = 0;
		a.elem = nullptr;
	}
	//init constructor
	vector3(std::initializer_list<T> lst) : sz(lst.size()), elem{ new T[sz] } {
		std::copy(lst.begin(), lst.end(), elem);
	}
	//distructor
	~vector3() { delete[] elem; }

	vector3& operator=(const vector3<T>& a) {
		if (this == &a) return *this;
		if (a.sz <= space) {
			for (int i = 0; i < a.sz; ++i)
				elem[i] = a.elem[i];
			sz = a.sz;
			return *this;
		}
		T* p = new T[a.sz];
		for (int i = 0; i < a.sz; ++i)
			p[i] = a.elem[i];
		delete[] elem;
		space = sz = a.sz;
		elem = p;
		return *this;
	}
	//move operator=
	vector3& operator=(vector3<T>&& a) {
		delete[] elem;
		elem = a.elem;
		sz = a.sz;
		a.elem = nullptr;
		a.sz = 0;
		return *this;
	}
	const T& operator[](int n) const { return elem[n]; }
	const T& operator[](int n) { return elem[n]; }

	void reserve(int newalloc) {
		if (newalloc <= space) return;
		T* p = new T[newalloc];
		for (int i = 0; i < sz; ++i)
			p[i] = elem[i];
		delete[] elem;
		elem = p;
		space = newalloc;
	}
	void push_back(const T& d) {
		if (space == 0)
			reserve(8);
		else if (sz == space)
			reserve(2 * space);
		elem[sz] = d;
		++sz;
	}
	int capacity() const {
		return space;
	}
	void resize(int newsize) {
		reserve(newsize);
		for (int i = sz; i < newsize; ++i)
			elem[i] = 0;
		sz = newsize;
	}
	int size() { return sz; }
};



