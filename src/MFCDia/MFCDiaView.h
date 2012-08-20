
// MFCDiaView.h : interface of the CMFCDiaView class
//

#pragma once
#include "AbstractMode.h"

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
	BOOL CMFCDiaView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
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
	std::vector<DiaEntity*>		m_selectedEntities;

	void selectEntity(const CPoint& rpoint);
};

#ifndef _DEBUG  // debug version in MFCDiaView.cpp
inline CMFCDiaDoc* CMFCDiaView::GetDocument() const
   { return reinterpret_cast<CMFCDiaDoc*>(m_pDocument); }
#endif

