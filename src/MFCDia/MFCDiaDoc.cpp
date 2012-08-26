
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
#include <algorithm>
#include "DiaArrow.h"

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
	m_saver = &m_binarySaver;
	m_loader = &m_binaryLoader;
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

BOOL CMFCDiaDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_saver->saveEnities(lpszPathName, m_entities);	
}


BOOL CMFCDiaDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	clearDocument();
	m_selectedEntities.clear();
	return m_loader->loadEnities(lpszPathName, &m_entities);
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

const std::list<DiaEntity*>* CMFCDiaDoc::getDrawEntities() const
{
	return &m_entities;
}

void CMFCDiaDoc::clearDocument()
{	
	for (std::list<DiaEntity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
	{		
		delete (*it);		
	}		
	m_entities.clear();
}

void CMFCDiaDoc::addEntity(DiaEntity* entity)
{
	DiaEntity::Type type = entity->type();
	if (type == DiaEntity::Arrow)
	{
		DiaArrow* pArrow = dynamic_cast<DiaArrow*>(entity);
		const DiaEntity* begin = pArrow->getBeginEntity();
		const DiaEntity* end = pArrow->getEndEntity();
		
		if ( !areAlreadyConnected(begin, end) )
		{
			m_entities.push_back(entity);		
		}
		else
		{
			delete entity;
		}
	}
	else
	{
		m_entities.push_front(entity);
	}
	UpdateAllViews(NULL);
}

bool CMFCDiaDoc::areAlreadyConnected(const DiaEntity* begin, const DiaEntity* end) const
{
	for (std::list<DiaEntity*>::const_reverse_iterator it = m_entities.crbegin(); it != m_entities.crend(); ++it)
	{		
		if ((*it)->type() != DiaEntity::Arrow)
			break;
		DiaArrow* pArrow = dynamic_cast<DiaArrow*>(*it);
		if (pArrow->getBeginEntity()->id() == begin->id() &&
			pArrow->getEndEntity()->id() == end->id() || 
			pArrow->getBeginEntity()->id() == end->id() &&
			pArrow->getEndEntity()->id() == begin->id())
		{
			return true;
		}		
	}	
	return false;
}

DiaEntity* CMFCDiaDoc::findEntity(const CPoint& point) const
{		
	for (std::list<DiaEntity*>::const_iterator it = m_entities.cbegin(); it != m_entities.cend(); ++it)
	{		
		if ((*it)->contains(point))
			return *it;	
	}		
	return NULL;
}

bool CMFCDiaDoc::findConnected(const DiaEntity* entity, std::list<DiaEntity*>* pList) const
{
	int needed_id = entity->id();

	for (std::list<DiaEntity*>::const_reverse_iterator it = m_entities.crbegin(); it != m_entities.crend(); ++it)
	{		
		if ((*it)->type() != DiaEntity::Arrow)
			break;
		DiaArrow* pArrow = dynamic_cast<DiaArrow*>(*it);
		if (pArrow->getBeginEntity()->id() == needed_id ||
			pArrow->getEndEntity()->id() == needed_id)
		{
			pList->push_back(*it);
		}		
	}	
	return true;
}

bool CMFCDiaDoc::selectEntity(const CPoint& rpoint)
{
	DiaEntity* pEntity = findEntity(rpoint);

	if (pEntity == NULL)
	{
		return false;
	}

	pEntity->setSelected(true);

	std::list<DiaEntity*> connections;

	findConnected(pEntity, &connections);

	for (std::list<DiaEntity*>::iterator it = connections.begin(); it != connections.end(); ++it)
	{
		(*it)->setSelected(true);
		m_selectedEntities.push_back(*it);
	}

	m_selectedEntities.push_back(pEntity);		
	return true;
}

bool CMFCDiaDoc::haveSelected() const
{
	return !m_selectedEntities.empty();
}

void CMFCDiaDoc::clearSelection()
{	
	for (std::list<DiaEntity*>::iterator it = m_selectedEntities.begin(); it != m_selectedEntities.end(); ++it)
	{
		(*it)->setSelected(false);		
	}
	m_selectedEntities.clear();
}

void CMFCDiaDoc::moveSelected(std::pair<LONG,LONG> vec)
{	
	for (std::list<DiaEntity*>::iterator it = m_selectedEntities.begin(); it != m_selectedEntities.end(); ++it)
	{
		(*it)->applyVec(vec);
	}	
}

void CMFCDiaDoc::deleteSelected()
{
	for (std::list<DiaEntity*>::iterator it = m_selectedEntities.begin(); it != m_selectedEntities.end(); ++it)
	{				
		m_entities.erase( std::remove(m_entities.begin(), m_entities.end(), *it), m_entities.end() );				
		delete *it;					
	}
	m_selectedEntities.clear();
}