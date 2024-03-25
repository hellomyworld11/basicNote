#include "Factory.h"
#include "Product.h"
#include <iostream>

Factory::Factory()
{

}



Factory::~Factory()
{

}

Product* Factory::CreateProduct(std::string proname)
{
	if ("A" == proname)
	{
		return new ConcreteProductA();
	}
	else if ("B" == proname)
	{
		return new ConcreteProductB();
	}
	return nullptr;
}



