#include "StdAfx.h"
#include "DiaRectangle.h"


DiaRectangle::DiaRectangle(int x1, int y1, int x2, int y2)	
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


DiaRectangle::~DiaRectangle(void)
{
}

void DiaRectangle::draw(CDC* pDC) const
{
	if (m_selected)
	{
		CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* pOldPen = pDC->SelectObject(&penBlue);

		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);

		pDC->SelectObject(pOldPen);
	}
	else
		pDC->Rectangle(m_x1, m_y1, m_x2, m_y2);
}

bool DiaRectangle::contains(const CPoint& rpoint) const
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

void DiaRectangle::applyVec(std::pair<LONG,LONG>& vec)
{
	long dx = vec.first;
	long dy = vec.second;

	m_x1 += dx;
	m_x2 += dx;
	m_y1 += dy;
	m_y2 += dy;
}

CPoint DiaRectangle::getCentralPoint() const
{
	return CPoint(m_x2 - (m_x2 - m_x1)/2, m_y2 - (m_y2 - m_y1)/2);
}

CPoint DiaRectangle::getCrossPoint(const CPoint& from, const CPoint& to) const
{	
	CPoint intersection_point;

	bool found = lineIntersection(from, to, CPoint(m_x1, m_y1), CPoint(m_x1, m_y2), &intersection_point);

	if (found)
		return intersection_point;

	found = lineIntersection(from, to, CPoint(m_x1, m_y2), CPoint(m_x2, m_y2), &intersection_point);

	if (found)
		return intersection_point;

	found = lineIntersection(from, to, CPoint(m_x2, m_y2), CPoint(m_x2, m_y1), &intersection_point);

	if (found)
		return intersection_point;

	found = lineIntersection(from, to, CPoint(m_x2, m_y1), CPoint(m_x1, m_y1), &intersection_point);

	if (found)
		return intersection_point;

	return to; // stub
}