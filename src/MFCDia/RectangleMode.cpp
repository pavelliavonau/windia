#include "StdAfx.h"
#include "RectangleMode.h"
#include "DiaRectangle.h"
#include "MFCDiaView.h"


RectangleMode::RectangleMode(CMFCDiaView* parent)
{
	mp_parentView = parent;
}

RectangleMode::~RectangleMode(void)
{
}

bool RectangleMode::isEnoughtItems() const
{
	return m_points.size() == 2;
}

DiaEntity* RectangleMode::createEntity() const
{
	CPoint leftH = m_points.front();
    CPoint rightD = m_points.back();
	return new DiaRectangle(leftH.x, leftH.y, rightD.x, rightD.y);
}

bool RectangleMode::isPreviewAvailable() const
{
	return !m_points.empty();
}

void RectangleMode::drawPreview(CDC* pDC) const
{
	CPoint leftH = m_points.front();
	pDC->Rectangle(leftH.x, leftH.y, m_mousePosition.x, m_mousePosition.y);
}

LPCTSTR RectangleMode::getCurrentCursor() const
{
	return IDC_ARROW;
}
