#include "StdAfx.h"
#include "HandMode.h"
#include "MFCDiaView.h"


HandMode::HandMode(CMFCDiaView* parent)
{
	mp_parentView = parent;
	m_isTracking = false;
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
	return NULL;		// WARNING: stub
}

bool HandMode::isPreviewAvailable() const
{
	return false;
}

void HandMode::drawPreview(CDC* pDC) const
{
}

LPCTSTR HandMode::getCurrentCursor() const
{
	return IDC_HAND;
}

void HandMode::OnLButtonDown(UINT Flags, CPoint Loc)
{
	if ( mp_parentView->haveSelected() )
	{		
		mp_parentView->clearSelection();
		pullPoint();
	}

	if(mp_parentView->selectEntity(Loc))	
	{
		pushPoint(Loc);
		mp_parentView->RedrawWindow();
		m_isTracking = true;
	}	
}

void HandMode::OnLButtonUp(UINT Flags, CPoint Loc)
{
	m_isTracking = false;
}

void HandMode::OnMouseMove(UINT nFlags, const CPoint& point)
{
	if ( m_isTracking )
	{		
		CPoint& oldPoint = pullPoint();		
		m_vec.first = point.x - oldPoint.x;
		m_vec.second = point.y - oldPoint.y;
		mp_parentView->moveSelected(m_vec);		
		pushPoint(point);
		//mp_parentView->RedrawWindow();		
	}
}