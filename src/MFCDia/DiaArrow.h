#pragma once
#include "diaconnectionentity.h"
class DiaArrow :
	public DiaConnectionEntity
{
public:
	DiaArrow(std::vector<DiaEntity*> link);
	virtual ~DiaArrow(void);	
	void draw(CDC* pDC) const;
	bool contains(const CPoint&) const;
	void applyVec(std::pair<LONG,LONG>&);
	CPoint getCentralPoint() const;
};

