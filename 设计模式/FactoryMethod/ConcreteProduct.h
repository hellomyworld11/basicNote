#include "Product.h"

class ConcreteProduct : public Product
{

public:
	ConcreteProduct();
	virtual ~ConcreteProduct();

	virtual void use();

};
