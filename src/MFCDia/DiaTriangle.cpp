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
	m_yA = yc - R;	

	dx = R * sqrt(3.0)/2;
	dy = R/2;

	m_xB = xc + dx;
	m_yB = yc + dy;

	m_xC = xc - dx;
	m_yC = m_yB;
}


DiaTriangle::~DiaTriangle(void)
{
}

void DiaTriangle::draw(CDC* pDC)
{
	pDC->MoveTo(m_xA, m_yA);
	pDC->LineTo(m_xB, m_yB);
	pDC->LineTo(m_xC, m_yC);
	pDC->LineTo(m_xA, m_yA);	
}

bool DiaTriangle::contains(const CPoint& rpoint)
{	   
	int s1 = wherePoint(m_xA, m_yA, m_xB, m_yB, rpoint.x, rpoint.y);
    int s2 = wherePoint(m_xB, m_yB, m_xC, m_yC, rpoint.x, rpoint.y);
    if (s2 * s1 <=0) return false;
    int s3 = wherePoint(m_xC, m_yC, m_xA, m_yA, rpoint.x, rpoint.y);
    if (s3 * s2 <= 0) return false;	
	return true;
}


int DiaTriangle::wherePoint(double ax, double ay, double bx, double by, double px, double py)
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

void DiaTriangle::applyVec(std::pair<LONG,LONG>& vec)
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

CPoint DiaTriangle::getCentralPoint()
{
	return CPoint(m_xCenter, m_yCenter);
}