#pragma once
#include <cstdlib>

class Allocator {
public:
	void* Allocate(size_t size)
	{
		obj* ptmpLink = nullptr;
		if (nullptr ==  m_freePos)
		{
			size_t realsize = size * m_sNewCount;
			m_freePos = (obj*)malloc(realsize);
			ptmpLink = m_freePos;
			for (size_t i = 0; i < m_sNewCount - 1; i++)
			{
				ptmpLink->next = (obj*)((char*)ptmpLink + size);
				ptmpLink = ptmpLink->next;
			}
			ptmpLink->next = nullptr;
		}
		ptmpLink = m_freePos;
		m_freePos = m_freePos->next;	
		return ptmpLink;
	}

	void Deallocate(void* p)
	{
		((obj*)p)->next = m_freePos;
		m_freePos = (obj*)p;
	}
private:
	struct obj {  //«∂»Î Ω÷∏’Î
		struct obj* next;
	};

	int m_sNewCount = 5;
	obj* m_freePos = nullptr;
};
