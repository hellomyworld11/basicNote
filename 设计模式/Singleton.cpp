#include "Singleton.h"
#include <iostream>


Singleton * Singleton::instance = nullptr;

Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	delete instance;
}

Singleton* Singleton::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Singleton;
	}
	return instance;
}

void Singleton::SingleOp()
{
	std::cout << "singleOp" << std::endl;
}

void Singleton::Test()
{
	Singleton *sg = Singleton::GetInstance();
	if (sg)
	{
		sg->SingleOp();
	}
}
