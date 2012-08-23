#pragma once
#include "diaentity.h"
class DiaEllipse :
	public DiaEntity
{
public:
	DiaEllipse(int x1, int y1, int x2, int y2);
	virtual ~DiaEllipse(void);
	void draw(CDC* pDC) const;
	bool contains(const CPoint&) const;
	void applyVec(std::pair<LONG,LONG>&);
	CPoint getCentralPoint() const;
	CPoint getCrossPoint(const CPoint& from, const CPoint& to) const;

private:	

	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;

	CPoint m_F1;
	CPoint m_F2;
};

