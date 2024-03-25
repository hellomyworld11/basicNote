

#include "AbstractFactory.h"
#include "AbstractProductA.h"
#include "AbstractProductB.h"


class ConcreteFactory1 : public AbstractFactory
{

public:
	ConcreteFactory1();
	virtual ~ConcreteFactory1();

	virtual AbstractProductA * createProductA();
	virtual AbstractProductB * createProductB();

};

