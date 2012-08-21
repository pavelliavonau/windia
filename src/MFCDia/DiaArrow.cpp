#include "StdAfx.h"
#include "DiaArrow.h"


DiaArrow::DiaArrow(std::vector<DiaEntity*> link)
{
	m_connectionSequence = link;
}


DiaArrow::~DiaArrow(void)
{
}

void DiaArrow::draw(CDC* pDC) const
{
	CPoint pFrom = m_connectionSequence.front()->getCentralPoint();
	CPoint pTo = m_connectionSequence.back()->getCentralPoint();
	pDC->MoveTo(pFrom.x, pFrom.y);
	pDC->LineTo(pTo.x, pTo.y);	
}

bool DiaArrow::contains(const CPoint& rpoint) const
{
	/*if (rpoint.x >= m_x1 &&
		rpoint.x <= m_x2 &&
		rpoint.y >= m_y1 &&
		rpoint.y <= m_y2)
	{
		return true;
	}
	else
	{
		return false;
	}*/
	return false;
}

void DiaArrow::applyVec(std::pair<LONG,LONG>& vec)
{
	/*long dx = vec.first;
	long dy = vec.second;

	m_x1 += dx;
	m_x2 += dx;
	m_y1 += dy;
	m_y2 += dy;*/
}

CPoint DiaArrow::getCentralPoint() const
{
	return CPoint();
}