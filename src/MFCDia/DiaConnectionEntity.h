#pragma once
#include "diaentity.h"
#include <list>

class DiaConnectionEntity :
	public DiaEntity
{
public:
	DiaConnectionEntity(void);
	virtual ~DiaConnectionEntity(void);

	void draw(CDC* pDC) const = 0;
	bool contains(const CPoint&) const = 0;
	void applyVec(const std::pair<LONG,LONG>&) = 0;

protected:
	std::list<DiaEntity*> m_connectionSequence;
};

