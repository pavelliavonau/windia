#include "StdAfx.h"
#include "EllipseMode.h"
#include "DiaEllipse.h"


EllipseMode::EllipseMode(void)
{
}

EllipseMode::~EllipseMode(void)
{
}

bool EllipseMode::isEnoughtItems() const
{
	return m_points.size() == 2;
}

DiaEntity* EllipseMode::createEntity() const
{
	CPoint leftH = m_points.front();
    CPoint rightD = m_points.back();
	return new DiaEllipse(leftH.x, leftH.y, rightD.x, rightD.y);
}

bool EllipseMode::isPreviewAvailable() const
{
	return !m_points.empty();
}

void EllipseMode::drawPreview(CDC* pDC) const
{
	CPoint leftH = m_points.front();
	pDC->Ellipse(leftH.x, leftH.y, m_mousePosition.x, m_mousePosition.y);
}

LPCTSTR EllipseMode::getCurrentCursor() const
{
	return IDC_ARROW;
}

AbstractMode::modes EllipseMode::getModeType() const
{
	return AbstractMode::ELLIPSE_MODE;
}