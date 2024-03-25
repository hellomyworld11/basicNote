#ifndef _Factory_H_
#define _Factory_H_
#include <string>
class Product;

class Factory
{
public:
	Factory();
	virtual ~Factory() = 0;

	static Product* CreateProduct(std::string proname);
	
};



#endif