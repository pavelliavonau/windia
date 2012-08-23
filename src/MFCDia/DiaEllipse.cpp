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
	if (m_selected)
	{
		CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));
		CPen* pOldPen = pDC->SelectObject(&penBlue);

		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);

		pDC->SelectObject(pOldPen);
	}
	else
		pDC->Ellipse(m_x1, m_y1, m_x2, m_y2);
}

bool DiaEllipse::contains(const CPoint& rpoint) const
{	
	double a2 = m_x2 - m_x1;				// a means larger axis
	double b2 = m_y2 - m_y1;				// b means smaller axis	

	if (a2 > b2)
	{
		double a = a2 / 2;					
		double b = b2 / 2;					

		double e = sqrt(1 - (b*b) / (a*a));
	
		double c = a * e;

		double centralX = m_x2 - a;

		double f1_x = centralX + c;
		double f1_y = m_y2 - b;

		double f2_x = centralX - c;
		double f2_y = f1_y;

		double d1 = sqrt(pow(rpoint.x - f1_x, 2) + pow(rpoint.y - f1_y, 2));
		double d2 = sqrt(pow(rpoint.x - f2_x, 2) + pow(rpoint.y - f2_y, 2));

		if (d1 + d2 <= a2)
			return true;
		else
			return false;	
	}
	else
	{
		double b = a2 / 2;					
		double a = b2 / 2;					

		double e = sqrt(1 - (b*b) / (a*a));
	
		double c = a * e;

		double centralY = m_y2 - a;

		double f1_y = centralY + c;
		double f1_x = m_x2 - b;

		double f2_y = centralY - c;
		double f2_x = f1_x;

		double d1 = sqrt(pow(rpoint.x - f1_x, 2) + pow(rpoint.y - f1_y, 2));
		double d2 = sqrt(pow(rpoint.x - f2_x, 2) + pow(rpoint.y - f2_y, 2));

		if (d1 + d2 <= b2)
			return true;
		else
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

CPoint DiaEllipse::getCrossPoint(const CPoint& from, const CPoint& to) const
{
	CPoint center = getCentralPoint();

	double distance = sqrt(pow(static_cast<double>(to.x) - from.x, 2) + pow(static_cast<double>(to.y) - from.y, 2));
	double distance_y = to.y - from.y;
	double distance_x = to.x - from.x;
	
	double sin_gamma = distance_y / distance;
	double cos_gamma = distance_x / distance;

	double a = (m_x2 - m_x1) / 2;				
	double b = (m_y2 - m_y1) / 2;				

	double radius = a*b / (sqrt( pow(b,2)*pow(cos_gamma,2) + pow(a,2)*pow(sin_gamma,2) ));

	double a1 = radius * cos_gamma;
	double b1 = radius * sin_gamma;

	double result_x = from.x + a1;
	double result_y = from.y + b1;

	if (to == center)
	{
		result_x = to.x - a1;
		result_y = to.y - b1;
	}	

	return CPoint(static_cast<int>(result_x), static_cast<int>(result_y));
}