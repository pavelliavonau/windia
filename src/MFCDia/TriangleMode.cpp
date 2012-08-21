#include "StdAfx.h"
#include "TriangleMode.h"
#include "DiaTriangle.h"
#include "MFCDiaView.h"


TriangleMode::TriangleMode(CMFCDiaView* parent)
{
	mp_parentView = parent;
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
	int yA = static_cast<int>(yc - R);	

	dx = R * sqrt(3.0)/2;
	dy = R/2;

	int xB = static_cast<int>(xc + dx);
	int yB = static_cast<int>(yc + dy);

	int xC = static_cast<int>(xc - dx);
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

