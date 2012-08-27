
// MFCDiaView.h : interface of the CMFCDiaView class
//

#pragma once
#include "AbstractMode.h"
#include "RectangleMode.h"
#include "HandMode.h"
#include "ArrowMode.h"
#include "EllipseMode.h"
#include "TriangleMode.h"

class DiaEntity;
class CMFCDiaDoc;

class CMFCDiaView : public CView
{
protected: // create from serialization only
	CMFCDiaView();
	DECLARE_DYNCREATE(CMFCDiaView)

// Attributes
public:
	CMFCDiaDoc* GetDocument() const;

// Operations
public:
	DiaEntity* findEntity(const CPoint& point) const;
	void addEntity(DiaEntity*);
	bool selectEntity(const CPoint& rpoint);
	bool haveSelected() const;
	void clearSelection();
	void moveSelected(const std::pair<LONG,LONG>&);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCDiaView();

	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnTriangle();
	afx_msg void OnArrow();
	afx_msg void OnHand();	
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnRButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnLButtonUp(UINT Flags, CPoint Loc);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	AbstractMode*				m_pmode;
	RectangleMode				m_rectangleMode;
	EllipseMode					m_ellipseMode;
	TriangleMode				m_triangleMode;
	ArrowMode					m_arrowMode;
	HandMode					m_handMode;		
};

#ifndef _DEBUG  // debug version in MFCDiaView.cpp
inline CMFCDiaDoc* CMFCDiaView::GetDocument() const
   { return reinterpret_cast<CMFCDiaDoc*>(m_pDocument); }
#endif

