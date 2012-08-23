
// MFCDiaView.cpp : implementation of the CMFCDiaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDia.h"
#endif

#include "MFCDiaDoc.h"
#include "MFCDiaView.h"
#include <vector>
#include "DiaEntity.h"
#include <iterator>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDiaView

IMPLEMENT_DYNCREATE(CMFCDiaView, CView)

BEGIN_MESSAGE_MAP(CMFCDiaView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_BUTTON_RECTANGLE, OnRectangle)
	ON_COMMAND(ID_BUTTON_HAND, OnHand)
	ON_COMMAND(ID_BUTTON_ARROW, OnArrow)
	ON_COMMAND(ID_BUTTON_ELLIPSE, OnEllipse)
	ON_COMMAND(ID_BUTTON_TRIANGLE, OnTriangle)
END_MESSAGE_MAP()

// CMFCDiaView construction/destruction

CMFCDiaView::CMFCDiaView()	:
	m_rectangleMode(this),
	m_ellipseMode(this),
	m_triangleMode(this),
	m_arrowMode(this),
	m_handMode(this)
{
	m_pmode = &m_rectangleMode;		//!< init mode
	// TODO: add construction code here

}

CMFCDiaView::~CMFCDiaView()
{
}

BOOL CMFCDiaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDiaView drawing

void CMFCDiaView::OnDraw(CDC* pDC)
{
	CMFCDiaDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;	

	const std::vector<DiaEntity*>* entities = pDoc->getDrawEntities();

	for (std::vector<DiaEntity*>::const_iterator it = entities->begin(); it != entities->end(); ++it)
	{
		(*it)->draw(pDC);		
	}		

	if (m_pmode->isPreviewAvailable())
	{
		m_pmode->drawPreview(pDC);
	}
}


// CMFCDiaView diagnostics

#ifdef _DEBUG
void CMFCDiaView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDiaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDiaDoc* CMFCDiaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDiaDoc)));
	return (CMFCDiaDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDiaView message handlers

BOOL CMFCDiaView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{      
	::SetCursor(AfxGetApp()->LoadStandardCursor(m_pmode->getCurrentCursor()));
	return TRUE;
}

void CMFCDiaView::OnRectangle()
{		
	m_pmode = &m_rectangleMode;
}

void CMFCDiaView::OnEllipse()
{	
	m_pmode = &m_ellipseMode;
}

void CMFCDiaView::OnTriangle()
{	
	m_pmode = &m_triangleMode;
}

void CMFCDiaView::OnArrow()
{	
	m_pmode = &m_arrowMode;
}

void CMFCDiaView::OnHand()
{	
	m_pmode = &m_handMode;
}

#include <WinUser.h>

void CMFCDiaView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{


}

void CMFCDiaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if ( nChar == VK_LCONTROL ||				// TODO: idea of multiple selection
	//	 nChar == VK_RCONTROL)
	//{
	//	int i= 0;
	//	i++;		
	//}
	if ( nChar == VK_DELETE )
	{
		GetDocument()->deleteSelected();
		RedrawWindow();
	}
}

void CMFCDiaView::OnRButtonDown(UINT Flags, CPoint Loc)
{
	m_pmode->OnRButtonDown(Flags, Loc);
}

void CMFCDiaView::OnLButtonDown(UINT Flags, CPoint Loc)
{
	m_pmode->OnLButtonDown(Flags, Loc);	
}

void CMFCDiaView::OnLButtonUp(UINT Flags, CPoint Loc)
{
	m_pmode->OnLButtonUp(Flags,Loc);
}

void CMFCDiaView::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pmode->OnMouseMove(nFlags, point);
}

bool CMFCDiaView::selectEntity(const CPoint& rpoint)
{
	return GetDocument()->selectEntity(rpoint);	
}

DiaEntity* CMFCDiaView::findEntity(const CPoint& point) const
{
	return GetDocument()->findEntity(point);
}

void CMFCDiaView::addEntity(DiaEntity* e)
{
	return GetDocument()->addEntity(e);
}

bool CMFCDiaView::haveSelected() const
{
	return GetDocument()->haveSelected();
}

void CMFCDiaView::clearSelection()
{
	GetDocument()->clearSelection();
}

void CMFCDiaView::moveSelected(std::pair<LONG,LONG> vec)
{
	GetDocument()->moveSelected(vec);
}