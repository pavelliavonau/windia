#include "StdAfx.h"
#include "ArrowMode.h"
#include "DiaArrow.h"


ArrowMode::ArrowMode(void)
{
}


ArrowMode::~ArrowMode(void)
{
}

bool ArrowMode::isEnoughtItems() const
{
	return m_entities.size() == 2;
}

DiaEntity* ArrowMode::createEntity() const
{
	return new DiaArrow(m_entities);
}

bool ArrowMode::isPreviewAvailable() const
{
	return !m_entities.empty();
}

void ArrowMode::drawPreview(CDC* pDC) const
{
	CPoint firstCenter = m_entities.front()->getCentralPoint();
	pDC->MoveTo(firstCenter.x, firstCenter.y);
	pDC->LineTo(m_mousePosition.x, m_mousePosition.y);	
}

LPCTSTR ArrowMode::getCurrentCursor() const
{
	return IDC_ARROW;
}

AbstractMode::modes ArrowMode::getModeType() const
{
	return AbstractMode::ARROW_MODE;
}