#include "Product.h"
#include "Factory.h"

class ConcreteFactory : public Factory
{

public:
	ConcreteFactory();
	virtual ~ConcreteFactory();

	virtual Product* factoryMethod();

};

