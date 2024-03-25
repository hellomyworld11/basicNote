

#include "AbstractFactory.h"
#include "AbstractProductA.h"
#include "AbstractProductB.h"

class ConcreteFactory2 : public AbstractFactory
{

public:
	ConcreteFactory2();
	virtual ~ConcreteFactory2();

	virtual AbstractProductA * createProductA();
	virtual AbstractProductB * createProductB();

};
