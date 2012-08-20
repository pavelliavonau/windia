#include "StdAfx.h"
#include "TriangleMode.h"
#include "DiaTriangle.h"


TriangleMode::TriangleMode(void)
{
}


TriangleMode::~TriangleMode(void)
{
}

bool TriangleMode::isEnoughtItems() const
{
	return m_points.size() == 2;
}

DiaEntity* TriangleMode::createEntity() const
{
	CPoint central = m_points.front();
    CPoint radial = m_points.back();
	return new DiaTriangle(central.x, central.y, radial.x, radial.y);
}

bool TriangleMode::isPreviewAvailable() const
{
	return !m_points.empty();
}

void TriangleMode::drawPreview(CDC* pDC) const
{
	CPoint leftH = m_points.front();

	int xc = leftH.x, 
		yc = leftH.y,
		xr = m_mousePosition.x, 
		yr = m_mousePosition.y;

	double dx = xr - xc;
	double dy = yr - yc;

	double R = sqrt(pow(dx, 2)+ pow(dy, 2));

	int xA = xc;
	int yA = yc - R;	

	dx = R * sqrt(3.0)/2;
	dy = R/2;

	int xB = xc + dx;
	int yB = yc + dy;

	int xC = xc - dx;
	int yC = yB;

	pDC->MoveTo(xA, yA);
	pDC->LineTo(xB, yB);
	pDC->LineTo(xC, yC);
	pDC->LineTo(xA, yA);
}

LPCTSTR TriangleMode::getCurrentCursor() const
{
	return IDC_ARROW;
}

AbstractMode::modes TriangleMode::getModeType() const
{
	return AbstractMode::RECTANGLE_MODE;
}