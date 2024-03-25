#include "Product.h"
#include <iostream>


Product::Product()
{
}


Product::~Product()
{
}

ConcreteProductA::ConcreteProductA() {

}



ConcreteProductA::~ConcreteProductA() {

}

void ConcreteProductA::Use()
{
	std::cout << "use productA" << std::endl;
}

ConcreteProductB::ConcreteProductB() {

}



ConcreteProductB::~ConcreteProductB() {

}

void ConcreteProductB::Use()
{
	std::cout << "use productB" << std::endl;
}