#pragma once
template<typename T>
class allocator
{
public:
	// ...
	T* allocate(int n);				// Выделение памяти для n объектов типа Т
	void deallocate(T* p, int n);		// Освобождение памяти, занятой n объектами типа Т с адреса р

	void construct(T* p, const T& v);	// Создание объекта типа Т созна чением v по адресу р
	void destroy(T* p);				// Уничтожение объекта Т по адресу р
};
