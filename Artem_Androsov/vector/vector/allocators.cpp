#include "allocators.h"

template<typename T>
T* allocator<T>::allocate(int n)
{
	// c
	//return static_cast<T*>(malloc(sizeof (T) * n));

	// c++
	return reinterpret_cast<T*>(new char[sizeof(T) * n]);
}

template<typename T>
void allocator<T>::deallocate(T* p, int n)
{
	//c
	free(p);
	//c++
	delete[] reinterpret_cast<char*>(p);
}

template<typename T>
void allocator<T>::construct(T* p, const T& v)
{
	//c

	//c++
	new(p) T(p);
}

template<typename T>
void allocator<T>::destroy(T* p)
{
	//c

	//c++
	p->~T();
}