#ifndef _PRODUCT_H_
#define _PRODUCT_H_

class Product
{
public:
	Product();
	virtual ~Product(); //注:析构函数声明为纯虚函数也需要实现
	virtual void Use() = 0;
	
};

class ConcreteProductA : public Product
{

public:
	ConcreteProductA();
	virtual ~ConcreteProductA();

	virtual void Use();

};
class ConcreteProductB : public Product
{
public:
	ConcreteProductB();
	virtual ~ConcreteProductB();

	virtual void Use();

};

#endif