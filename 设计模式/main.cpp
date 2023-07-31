#include "Factory.h"
#include <iostream>

int main(int argc, char **argv)
{
	Factory *factory = new ConcreteFactory();
	Product *p = factory->CreateProduct();

	getchar();
	return 0;
}