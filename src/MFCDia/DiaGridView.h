#pragma once

#include "grid/GXVW.h"
#include "DiaEntity.h"

#include <map>
#include <list>

class CMFCDiaDoc;

class DiaGridView : public CGXGridView
{
protected:
	DiaGridView();
	DECLARE_DYNCREATE(DiaGridView);
	
	// Attributes
public:
	CMFCDiaDoc* GetDocument();

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGLGridView)
public:
	virtual void OnDraw(CDC* pDC) override;  // overridden to draw this view
	virtual void OnInitialUpdate() override;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
	virtual void OnClickedButtonRowCol(ROWCOL nHitRow, ROWCOL nHitCol) override;
  virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0 ) override;
  virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0) override;
protected:
	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~DiaGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif                         

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(COGLGridView)
	//afx_msg void OnViewProperties();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()

#ifndef _DEBUG	// debug version in OGLGrvw.cpp
inline CMFCDiaDoc* DiaGridView::GetDocument()
{ return (CMFCDiaDoc*)m_pDocument; }
#endif                       

private:
	const char* getStringFigureTypeName(DiaEntity::Type type) const;
	const char* getStringContourTypeName(int type) const;
	void setEntityPenColor(ROWCOL entityNumber, COLORREF colorRef);
	void setEntityPenStyle(ROWCOL entityNumber, int penStyle);
	DiaEntity* findEntityWithRow(ROWCOL entityNumber, CMFCDiaDoc* pDoc);
	int getIntegerTypeOfStyle(CString stype);
	void setEntityCentralPoint(ROWCOL entityNumber, CPoint);
  const DiaEntity* GetRowData(ROWCOL row);

	std::map<CString,int>					m_lineTypesMap;
	std::map<int ,const char*>				m_stringContourTypeNameMap;
	std::map<DiaEntity::Type ,const char*>	m_stringFigureTypeNameMap;

  const std::list<DiaEntity*>*          m_entities;
  //std::list<DiaEntity*>::const_reverse_iterator   m_entities_iterator;
  //ROWCOL  m_previousRow;
};

