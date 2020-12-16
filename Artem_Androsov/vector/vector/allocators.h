#pragma once
template<typename T>
class allocator
{
public:
	// ...
	T* allocate(int n);				// ��������� ������ ��� n �������� ���� �
	void deallocate(T* p, int n);		// ������������ ������, ������� n ��������� ���� � � ������ �

	void construct(T* p, const T& v);	// �������� ������� ���� � ����� ������ v �� ������ �
	void destroy(T* p);				// ����������� ������� � �� ������ �
};
