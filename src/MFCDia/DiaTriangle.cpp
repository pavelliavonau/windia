#include "StdAfx.h"
#include "DiaTriangle.h"
#include <cmath>


DiaTriangle::DiaTriangle(LONG xc, LONG yc, LONG xr, LONG yr)
{
	m_xCenter = xc;
	m_yCenter = yc;		

	double dx = xr - xc;
	double dy = yr - yc;

	double R = sqrt(pow(dx, 2)+ pow(dy, 2));	

	m_xA = xc;
	m_yA = static_cast<int>(yc - R);	

	dx = R * sqrt(3.0)/2;
	dy = R/2;

	m_xB = static_cast<int>(xc + dx);
	m_yB = static_cast<int>(yc + dy);

	m_xC = static_cast<int>(xc - dx);
	m_yC = m_yB;
}

DiaTriangle::DiaTriangle(LONG xA, LONG yA, LONG xB, LONG yB, LONG xC, LONG yC) :
	m_xA(xA),
	m_yA(yA),
	m_xB(xB),
	m_yB(yB),
	m_xC(xC),
	m_yC(yC)
{
	
	m_xCenter = xA;
	m_yCenter = yC - (yC - yA) / 2;
}


DiaTriangle::~DiaTriangle(void)
{
}

void DiaTriangle::draw(CDC* pDC) const
{	

	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(m_penStyle, 1, m_penColor);

	if (m_selected)
	{		
		pOldPen = pDC->SelectObject(&m_penBlue);
	}
	else
	{
		pOldPen = pDC->SelectObject(&pen);
	}

	drawTriamgle(pDC);
	pDC->SelectObject(pOldPen);
}

void DiaTriangle::drawTriamgle(CDC* pDC) const
{
	CPoint pts[3];
	pts[0].x = m_xA;
	pts[0].y = m_yA;

	pts[1].x = m_xB;
	pts[1].y = m_yB;

	pts[2].x = m_xC;
	pts[2].y = m_yC;
	
	pDC->Polygon(pts, 3);
}

bool DiaTriangle::contains(const CPoint& rpoint) const
{	   
	int s1 = wherePoint(m_xA, m_yA, m_xB, m_yB, rpoint.x, rpoint.y);
    int s2 = wherePoint(m_xB, m_yB, m_xC, m_yC, rpoint.x, rpoint.y);
    if (s2 * s1 <=0) return false;
    int s3 = wherePoint(m_xC, m_yC, m_xA, m_yA, rpoint.x, rpoint.y);
    if (s3 * s2 <= 0) return false;	
	return true;
}


int DiaTriangle::wherePoint(double ax, double ay, double bx, double by, double px, double py) const
{
	double s = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
	if (s>0) 
	{
		return 1;
	}
	else 
		if (s<0) 
			return -1;
		else 
			return 0;	
}

void DiaTriangle::applyVec(const std::pair<LONG,LONG>& vec)
{
	long dx = vec.first;
	long dy = vec.second;

	m_xA += dx;
	m_xB += dx;
	m_xC += dx;
	m_xCenter += dx;
	m_yA += dy;
	m_yB += dy;
	m_yC += dy;
	m_yCenter += dy;
}

CPoint DiaTriangle::getCentralPoint() const
{
	return CPoint(m_xCenter, m_yCenter);
}

CPoint DiaTriangle::getCrossPoint(const CPoint& from, const CPoint& to) const
{
	CPoint intersection_point;

	bool found = lineIntersection(from, to, CPoint(m_xA , m_yA), CPoint(m_xB , m_yB), &intersection_point);

	if (found)
		return intersection_point;

	found = lineIntersection(from, to, CPoint(m_xB, m_yB), CPoint(m_xC, m_yC), &intersection_point);

	if (found)
		return intersection_point;

	found = lineIntersection(from, to, CPoint(m_xC , m_yC), CPoint(m_xA , m_yA), &intersection_point);

	if (found)
		return intersection_point;	

	return CPoint(m_xA , m_yA); // stub
}