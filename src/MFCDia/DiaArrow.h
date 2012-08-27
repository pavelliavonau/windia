#pragma once
#include "diaconnectionentity.h"

class DiaArrow :
	public DiaConnectionEntity
{
public:
	DiaArrow(std::list<DiaEntity*> link);
	virtual ~DiaArrow(void);	
	void draw(CDC* pDC) const;
	bool contains(const CPoint&) const;
	void applyVec(const std::pair<LONG,LONG>&);
	CPoint getCentralPoint() const;
	CPoint getCrossPoint(const CPoint& from, const CPoint& to) const;
	virtual DiaEntity::Type type() const { return DiaEntity::Arrow; };
	const DiaEntity* getBeginEntity() const;
	const DiaEntity* getEndEntity() const;

private:
	void drawArrow(CDC* pDC) const;
};

