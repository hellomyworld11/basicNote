#include "Factory.h"
#include "Product.h"
#include <iostream>

int main(int argc, char **argv)
{
	Product * prod = Factory::CreateProduct("A");

	prod->Use();

	delete prod;
	getchar();
	return 0;
}