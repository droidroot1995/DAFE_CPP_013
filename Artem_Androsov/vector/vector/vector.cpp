#include <iostream>
#include "vector1.h"
#include "vector2.h"
#include "vector3.h"

int main()
{
	// Vector1 using
	{
		vector1 v11(5);
		v11.set(0, 10);
		v11.set(1, 23);
		v11.set(2, 3);
		v11.set(3, 23);
		v11.set(4, 14);

		std::cout << "v11 size is " << v11.size() << std::endl << std::endl;

		std::cout << v11.get(0) << ' ' << v11.get(1) << ' ' << v11.get(2) << ' ' << v11.get(3) << ' ' << v11.get(4) << std::endl;
		std::cout << std::endl;
	}

	// vector2 using
	{
		vector2 v21{ 1, 2, 3, 4, 5 };
		vector2 v22{ 6,7,8,9,0 };
		vector2 v23(4);
		const vector2 v24(v21);

		vector2 v25(2);
		v25.set(0, 10);
		v25.set(1, 23);

		std::cout << "v21 size is " << v21.size() << std::endl;
		std::cout << "v22 size is " << v22.size() << std::endl;
		std::cout << "v23 size is " << v23.size() << std::endl;
		std::cout << "v24 size is " << v24.size() << std::endl;
		std::cout << "v25 size is " << v25.size() << std::endl;
		std::cout << std::endl;

		v25 = v23;
		std::cout << "v25 = v23" << std::endl << "v25 size is " << v25.size() << std::endl;
		std::cout << std::endl;


		std::cout << "v22[2] is " << v22[2] << std::endl;
		std::cout << std::endl;

		v22[2] = 10;
		std::cout << "v22[2] is " << v22[2] << std::endl;
		std::cout << std::endl;

		std::cout << "const v21[4] is " << v21[4] << std::endl;
		std::cout << std::endl;
	}

	//vector3 using
	{

	}
}