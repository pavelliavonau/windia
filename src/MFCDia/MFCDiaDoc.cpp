
// MFCDiaDoc.cpp : implementation of the CMFCDiaDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDia.h"
#endif

#include "MFCDiaDoc.h"

#include <propkey.h>
#include "DiaRectangle.h"
#include "RectangleMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCDiaDoc

IMPLEMENT_DYNCREATE(CMFCDiaDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCDiaDoc, CDocument)	
END_MESSAGE_MAP()


// CMFCDiaDoc construction/destruction

CMFCDiaDoc::CMFCDiaDoc() 
{
	// TODO: add one-time construction code here	
}

CMFCDiaDoc::~CMFCDiaDoc()
{
	clearDocument();
}

BOOL CMFCDiaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	clearDocument();

	return TRUE;
}

// CMFCDiaDoc serialization

void CMFCDiaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCDiaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCDiaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCDiaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCDiaDoc diagnostics

#ifdef _DEBUG
void CMFCDiaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCDiaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCDiaDoc commands

const std::vector<DiaEntity*>* CMFCDiaDoc::getDrawEntities() const
{
	return &m_entities;
}

void CMFCDiaDoc::clearDocument()
{
	std::vector<DiaEntity*>::iterator it = m_entities.begin();
	while(it != m_entities.end())
	{		
		delete (*it);
		it++;
	}		
	m_entities.clear();
}

void CMFCDiaDoc::addEntity(DiaEntity* entity)
{
	m_entities.push_back(entity);
	UpdateAllViews(NULL);
}

DiaEntity* CMFCDiaDoc::findEntity(const CPoint& point) const
{	
	std::vector<DiaEntity*>::const_iterator it = m_entities.cbegin();
	while(it != m_entities.cend())
	{		
		if ((*it)->contains(point))
			return *it;
		it++;
	}		
	return NULL;
}

bool CMFCDiaDoc::selectEntity(const CPoint& rpoint)
{
	DiaEntity* pEntity = findEntity(rpoint);

	if (pEntity == NULL)
	{
		return false;
	}

	pEntity->setSelected(true);
	m_selectedEntities.push_back(pEntity);		
	return true;
}

bool CMFCDiaDoc::haveSelected() const
{
	return !m_selectedEntities.empty();
}

void CMFCDiaDoc::clearSelection()
{
	std::vector<DiaEntity*>::iterator it = m_selectedEntities.begin();
	while(it != m_selectedEntities.end())
	{
		(*it)->setSelected(false);
		it++;
	}
	m_selectedEntities.clear();
}

void CMFCDiaDoc::moveSelected(std::pair<LONG,LONG> vec)
{
	std::vector<DiaEntity*>::iterator it = m_selectedEntities.begin();
	while(it != m_selectedEntities.end())
	{
		(*it)->applyVec(vec);
		it++;
	}	
}