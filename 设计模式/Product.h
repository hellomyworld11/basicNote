#ifndef _PRODUCT_H_
#define _PRODUCT_H_

class Product
{
public:
	virtual ~Product() = 0 ; //注:析构函数声明为纯虚函数也需要实现
protected:
	Product();
	
};

class ConcreteProduct : public Product
{
public:
	ConcreteProduct();
	~ConcreteProduct();
};


#endif