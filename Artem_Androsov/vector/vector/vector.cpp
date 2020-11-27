#include <iostream>
#include "vector1.h"
#include "vector2.h"
#include "vector3.h"

int main()
{
	vector1 v11(5);
	v11.set(0, 10);
	v11.set(1, 23);
	v11.set(2, 3);
	v11.set(3, 23);
	v11.set(4, 14);

	std::cout << v11.size() << std::endl << std::endl;

	std::cout << v11.get(0) << std::endl;
	std::cout << v11.get(1) << std::endl;
	std::cout << v11.get(2) << std::endl;
	std::cout << v11.get(3) << std::endl;
	std::cout << v11.get(4) << std::endl;
}