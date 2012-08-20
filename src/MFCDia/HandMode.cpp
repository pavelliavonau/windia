#include "StdAfx.h"
#include "HandMode.h"


HandMode::HandMode(void)
{
}


HandMode::~HandMode(void)
{
}

bool HandMode::isEnoughtItems() const
{
	return false;
}

DiaEntity* HandMode::createEntity() const
{
	/*CPoint leftH = m_points.front();
    CPoint rightD = m_points.back();
	return new DiaRectangle(leftH.x, leftH.y, rightD.x, rightD.y);*/
	return NULL;
}

bool HandMode::isPreviewAvailable() const
{
	return false;
}

void HandMode::drawPreview(CDC* pDC) const
{
	/*CPoint leftH = m_points.front();
	pDC->Rectangle(leftH.x, leftH.y, m_mousePosition.x, m_mousePosition.y);*/
}

LPCTSTR HandMode::getCurrentCursor() const
{
	return IDC_HAND;
}

AbstractMode::modes HandMode::getModeType() const
{
	return AbstractMode::HAND_MODE;
}