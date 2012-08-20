#pragma once
#include "diaentity.h"
#include <vector>

class DiaConnectionEntity :
	public DiaEntity
{
public:
	DiaConnectionEntity(void);
	virtual ~DiaConnectionEntity(void);

	void draw(CDC* pDC) = 0;
	bool contains(const CPoint&) = 0;
	void applyVec(std::pair<LONG,LONG>&) = 0;

protected:
	std::vector<DiaEntity*> m_connectionSequence;
};

