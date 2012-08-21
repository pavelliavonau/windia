#include "StdAfx.h"
#include "DiaEllipse.h"


DiaEllipse::DiaEllipse(int x1, int y1, int x2, int y2)
{
	if (x1 > x2)
	{
		int t = x2;
		x2 = x1;
		x1 = t;
	}
	if (y1 > y2)
	{
		int t = y2;
		y2 = y1;
		y1 = t;
	}
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
}


DiaEllipse::~DiaEllipse(void)
{
}

void DiaEllipse::draw(CDC* pDC) const
{
	pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);
}

bool DiaEllipse::contains(const CPoint& rpoint) const
{
	if (rpoint.x >= m_x1 &&
		rpoint.x <= m_x2 &&
		rpoint.y >= m_y1 &&
		rpoint.y <= m_y2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DiaEllipse::applyVec(std::pair<LONG,LONG>& vec)
{
	long dx = vec.first;
	long dy = vec.second;

	m_x1 += dx;
	m_x2 += dx;
	m_y1 += dy;
	m_y2 += dy;
}

CPoint DiaEllipse::getCentralPoint() const
{
	return CPoint(m_x2 - (m_x2 - m_x1)/2, m_y2 - (m_y2 - m_y1)/2);
}
