#pragma once
#include "allocator.h"

class A {
public:
	static Allocator alloc;
	static void* operator new(size_t size)
	{
		return alloc.Allocate(size);
	}

	static void operator delete(void* phead)
	{
		alloc.Deallocate(phead);
	}


	int m_i;
	int m_j;
};

Allocator A::alloc;