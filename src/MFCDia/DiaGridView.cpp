#include "StdAfx.h"
#include "DiaGridView.h"
#include "MFCDiaDoc.h"


/////////////////////////////////////////////////////////////////////////////
// DiaGridView

IMPLEMENT_DYNCREATE(DiaGridView, CGXGridView)

DiaGridView::DiaGridView()
{
  m_lineTypesMap.insert( std::pair<CString,int>("solid",PS_SOLID) );
  m_lineTypesMap.insert( std::pair<CString,int>("dash",PS_DASH) );
  m_lineTypesMap.insert( std::pair<CString,int>("dashdot",PS_DASHDOT) );
  m_lineTypesMap.insert( std::pair<CString,int>("dashdotdot",PS_DASHDOTDOT) );

  m_stringFigureTypeNameMap.insert( std::pair<DiaEntity::Type, const char*>(DiaEntity::Arrow, "arrow") );
  m_stringFigureTypeNameMap.insert( std::pair<DiaEntity::Type, const char*>(DiaEntity::Rectangle, "rectangle") );
  m_stringFigureTypeNameMap.insert( std::pair<DiaEntity::Type, const char*>(DiaEntity::Ellipse, "ellipse") );
  m_stringFigureTypeNameMap.insert( std::pair<DiaEntity::Type, const char*>(DiaEntity::Triangle, "triangle") );

  m_stringContourTypeNameMap.insert( std::pair<int,const char*>(PS_SOLID, "solid") );
  m_stringContourTypeNameMap.insert( std::pair<int,const char*>(PS_DASH, "dash") );
  m_stringContourTypeNameMap.insert( std::pair<int,const char*>(PS_DASHDOT, "dashdot") );
  m_stringContourTypeNameMap.insert( std::pair<int,const char*>(PS_DASHDOTDOT, "dashdotdot") );
}

DiaGridView::~DiaGridView()
{
}

void DiaGridView::OnDraw(CDC* pDC)
{
	CMFCDiaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CGXGridView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// COGLGridView diagnostics

#ifdef _DEBUG
void DiaGridView::AssertValid() const
{
  CGXGridView::AssertValid();
}

void DiaGridView::Dump(CDumpContext& dc) const
{
	CGXGridView::Dump(dc);
}

CMFCDiaDoc* DiaGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDiaDoc)));
	return (CMFCDiaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGLGridView message handlers

void DiaGridView::OnInitialUpdate()
{
	// Call the base class OnInitialUpdate. This call is
	// essential for grid specific intialization (In
	// contrast to GXInit which performs application specific
	// intialization)
	CGXGridView::OnInitialUpdate();

	// Disable Undo mechanism for the following commands.
	// Objective Grid has a built in Undo/Redo  architecture
	// that can be disabled/enabled with this call.
	// We disable it here so that users are not able to
	// rollback changes that we make in code.
	GetParam()->EnableUndo(FALSE);	

  CMFCDiaDoc* pDoc = GetDocument();

  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;
  m_entities = pDoc->getDrawEntities();

	SetRowCount(0);
	SetColCount(5);

	SetValueRange(CGXRange(0, 1), "figure type");
	SetValueRange(CGXRange(0, 2), "center x");
	SetValueRange(CGXRange(0, 3), "center y");
	SetValueRange(CGXRange(0, 4), "line type");
	SetValueRange(CGXRange(0, 5), "line color");

	// Re-enable undo mechanism
	GetParam()->EnableUndo(TRUE);
}

void DiaGridView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CMFCDiaDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

  m_entities = pDoc->getDrawEntities();

	SetRowCount(m_entities->size());

  Redraw();
}

void DiaGridView::OnClickedButtonRowCol(ROWCOL nHitRow, ROWCOL nHitCol)
{
	switch (nHitCol)
	{

	case 5:
		{
			CGXStyle style;
			GetStyleRowCol(nHitRow, nHitCol, style);

			CColorDialog dlg(style.GetInterior().GetColor());

			COLORREF rgbColor;

			if (dlg.DoModal() == IDOK)
			{
				rgbColor = dlg.GetColor();
				style.SetInterior(rgbColor);
				setEntityPenColor(nHitRow, rgbColor);
			}

			StoreStyleRowCol(nHitRow, nHitCol, &style);
			break;
		}
	default: break;
	}
}

int DiaGridView::getIntegerTypeOfStyle(CString stype)
{
	std::map<CString,int>::iterator iter = m_lineTypesMap.find(stype);
	if (iter == m_lineTypesMap.end() )
	{
		return PS_SOLID;
	}
	else
	{
		return iter->second;
	}
}

const char* DiaGridView::getStringFigureTypeName(DiaEntity::Type type) const 
{
	return m_stringFigureTypeNameMap.find(type)->second;
}

void DiaGridView::setEntityCentralPoint(ROWCOL entityNumber, CPoint point)
{
	CMFCDiaDoc* pDoc = GetDocument();
	DiaEntity* e = findEntityWithRow(entityNumber, pDoc);
	e->setCentralPoint(point);	
	pDoc->UpdateAllViews(NULL);
}

void DiaGridView::setEntityPenColor(ROWCOL entityNumber, COLORREF colorRef)
{
	CMFCDiaDoc* pDoc = GetDocument();
	DiaEntity* e = findEntityWithRow(entityNumber, pDoc);
	e->setContourColor(colorRef);	
	pDoc->UpdateAllViews(NULL);
}

void DiaGridView::setEntityPenStyle(ROWCOL entityNumber, int penStyle)
{
	CMFCDiaDoc* pDoc = GetDocument();
	DiaEntity* e = findEntityWithRow(entityNumber, pDoc);
	e->setContourStyle(penStyle);
	pDoc->UpdateAllViews(NULL);
}

DiaEntity* DiaGridView::findEntityWithRow(ROWCOL entityNumber, CMFCDiaDoc* pDoc)
{
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return NULL;

	const std::list<DiaEntity*>* entities = pDoc->getDrawEntities();

	int i = 0;
  auto it = entities->crbegin();
	for (; it != entities->crend(); ++it)
	{
		i++;
		if (entityNumber == i)
		{
			break;
		}
	}
	return *it;
}

const char* DiaGridView::getStringContourTypeName(int type) const 
{
	return m_stringContourTypeNameMap.find(type)->second;
}

BOOL DiaGridView::GetStyleRowCol( ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType )
{
  auto cell = GetRowData(nRow);
  if( !cell )
    return FALSE;

  CPoint point = cell->getCentralPoint();

  switch(nCol)
  {
    case 1:
      style.SetValue(getStringFigureTypeName( cell->type() ));
    return TRUE;

    case 2:
      style.SetValue(point.x);
    return TRUE;

    case 3:
      style.SetValue(point.y);
      return TRUE;
    case 4:
      style
        .SetControl(GX_IDS_CTRL_COMBOBOX)
        .SetChoiceList("solid\ndash\ndashdot\ndashdotdot")
        .SetValue(getStringContourTypeName( cell->getContourStyle() ));
      return TRUE;
    case 5:
      style
        .SetControl(GX_IDS_CTRL_HOTSPOT)	
        .SetInterior(cell->getContourColor());
      return TRUE;
  }

  return FALSE;
}

const DiaEntity* DiaGridView::GetRowData( ROWCOL row )
{
  if( row == 0 || row > m_entities->size() )
    return NULL;

  auto it = m_entities->crbegin();

  while( row != 1 )
    ++it,row--;

  return *it;
}

BOOL DiaGridView::StoreStyleRowCol( ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt /*= gxOverride*/, int nType /*= 0*/ )
{
  auto cell = GetRowData(nRow);
  if( !cell )
    return FALSE;

  switch (nCol)
  {
  case 2:
    {
      CGXStyle styleY;
      GetStyleRowCol(nRow, nCol + 1, styleY);

      CPoint point( pStyle->GetLongValue(), styleY.GetLongValue() );

      setEntityCentralPoint( nRow, point );
      break;
    }
  case 3:
    {
      CGXStyle styleX;
      GetStyleRowCol(nRow, nCol - 1, styleX);

      CPoint point( styleX.GetLongValue(), pStyle->GetLongValue() );

      setEntityCentralPoint(nRow, point);
      break;
    }
  case 4:
    {
      int istyle = getIntegerTypeOfStyle(pStyle->GetValue());

      setEntityPenStyle(nRow, istyle);
      break;
    }
  }
  return TRUE;
}
