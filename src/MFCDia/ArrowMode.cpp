#include "StdAfx.h"
#include "ArrowMode.h"
#include "DiaArrow.h"
#include "MFCDiaView.h"


ArrowMode::ArrowMode(CMFCDiaView * parent)	
{
	mp_parentView = parent;
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

void ArrowMode::OnLButtonDown(UINT Flags, CPoint Loc)
{
	DiaEntity* pEntity = mp_parentView->findEntity(Loc);
	if (pEntity == NULL)
		return;
	pushEntity(pEntity);
	if( isEnoughtItems() )
	{
		DiaEntity* e = createEntity();		
		mp_parentView->addEntity(e);
		resetMode();		
	}
}

void ArrowMode::OnLButtonUp(UINT Flags, CPoint Loc)
{

}

void ArrowMode::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( isPreviewAvailable() )
	{
		setMousePos(point);
		mp_parentView->RedrawWindow();
	}
}