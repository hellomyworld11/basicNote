#include "A.h"
#include <iostream>
int main()
{
	A* arr[100];
	for (int i = 0; i < 20; i++)
	{
		arr[i] = new A();
		std::cout << "Ö¸Õë: " << arr[i] << std::endl;
	}
	for (int i = 0; i < 20; i++)
	{
		delete arr[i];
	}
	getchar();
	return 0;
}