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
	DiaEntity* fromEntity = m_entities.front();	

	CPoint fromCenter = fromEntity->getCentralPoint();	
	CPoint pFrom = fromEntity->getCrossPoint( fromCenter, m_mousePosition );	
	
	if (fromEntity->contains(m_mousePosition))
		return;

	pDC->MoveTo(pFrom.x, pFrom.y);
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
	tryCreateEntity();
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