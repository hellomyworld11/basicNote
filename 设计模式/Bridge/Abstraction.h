///////////////////////////////////////////////////////////
//  Abstraction.h
//  Implementation of the Class Abstraction
//  Created on:      03-十月-2014 18:12:43
//  Original author: colin
#include "Implementor.h"

class Abstraction
{

public:
	Abstraction();
	virtual ~Abstraction();

	Abstraction(Implementor* imp);
	virtual void operation();

protected:
	Implementor* m_pImp;

};

