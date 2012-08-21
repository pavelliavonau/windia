
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
//#include "RectangleMode.h"
//#include "HandMode.h"
//#include "ArrowMode.h"
//#include "EllipseMode.h"
//#include "TriangleMode.h"

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
	ON_COMMAND(ID_BUTTON_RECTANGLE, OnRectangle)
	ON_COMMAND(ID_BUTTON_HAND, OnHand)
	ON_COMMAND(ID_BUTTON_ARROW, OnArrow)
	ON_COMMAND(ID_BUTTON_ELLIPSE, OnEllipse)
	ON_COMMAND(ID_BUTTON_TRIANGLE, OnTriangle)
END_MESSAGE_MAP()

// CMFCDiaView construction/destruction

CMFCDiaView::CMFCDiaView()	
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
	
	if (m_pmode->isPreviewAvailable())
	{
		m_pmode->drawPreview(pDC);
	}

	const std::vector<DiaEntity*>* entities = pDoc->getDrawEntities();

	std::vector<DiaEntity*>::const_iterator it = entities->cbegin();
	while(it != entities->cend())
	{
		(*it)->draw(pDC);
		it++;
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

void CMFCDiaView::OnRButtonDown(UINT Flags, CPoint Loc)
{
	m_pmode->resetMode();
	RedrawWindow();
}

void CMFCDiaView::OnLButtonDown(UINT Flags, CPoint Loc)
{
	AbstractMode::modes modeType = m_pmode->getModeType();

	switch (modeType)
	{
	case AbstractMode::RECTANGLE_MODE:
	case AbstractMode::ELLIPSE_MODE:
	case AbstractMode::TRIANGLE_MODE:
		{
			m_pmode->pushPoint(Loc);
			if( m_pmode->isEnoughtItems() )
			{
				DiaEntity* e = m_pmode->createEntity();
				CMFCDiaDoc* pDoc = GetDocument();
				pDoc->addEntity(e);
				m_pmode->resetMode();		
			}
			break;
		}
	case AbstractMode::ARROW_MODE:
		{
			DiaEntity* pEntity = GetDocument()->findEntity(Loc);
			if (pEntity == NULL)
				return;
			m_pmode->pushEntity(pEntity);
			if( m_pmode->isEnoughtItems() )
			{
				DiaEntity* e = m_pmode->createEntity();
				CMFCDiaDoc* pDoc = GetDocument();
				pDoc->addEntity(e);
				m_pmode->resetMode();		
			}
			break;
		}

	case AbstractMode::HAND_MODE:
		{
			selectEntity(Loc);
			break;
		}	
	}
}

void CMFCDiaView::OnLButtonUp(UINT Flags, CPoint Loc)
{
	if (AbstractMode::HAND_MODE == m_pmode->getModeType() &&
		!m_selectedEntities.empty())
	{
		std::vector<DiaEntity*>::iterator it = m_selectedEntities.begin();
		while(it != m_selectedEntities.end())
		{
			(*it)->setSelected(false);
			it++;
		}	
		m_pmode->pullPoint();
		m_selectedEntities.clear();
	}
}

void CMFCDiaView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pmode->isPreviewAvailable())
	{
		m_pmode->setMousePos(point);
		RedrawWindow();
	}

	if (AbstractMode::HAND_MODE == m_pmode->getModeType() &&
		!m_selectedEntities.empty())
	{
		CPoint oldPoint = m_pmode->pullPoint();
		std::pair<LONG,LONG> vec;
		vec.first = point.x - oldPoint.x;
		vec.second = point.y - oldPoint.y;

		std::vector<DiaEntity*>::iterator it = m_selectedEntities.begin();
		while(it != m_selectedEntities.end())
		{
			(*it)->applyVec(vec);
			it++;
		}	
		m_pmode->pushPoint(point);
		RedrawWindow();
	}	
}

void CMFCDiaView::selectEntity(const CPoint& rpoint)
{
	CMFCDiaDoc* pDoc = GetDocument();

	DiaEntity* pEntity = pDoc->findEntity(rpoint);

	if (pEntity == NULL)
	{
		return;
	}

	pEntity->setSelected(true);
	m_selectedEntities.push_back(pEntity);	
	m_pmode->pushPoint(rpoint);
}