
// MFCDiaDoc.h : interface of the CMFCDiaDoc class
//


#pragma once
#include <list>
#include "AbstractMode.h"
#include "DiaBinarySaver.h"
#include "DiaBinaryLoader.h"

class DiaEntity;

class CMFCDiaDoc : public CDocument
{
protected: // create from serialization only
	CMFCDiaDoc();
	DECLARE_DYNCREATE(CMFCDiaDoc)

// Attributes
public:

// Operations
public:
	const std::list<DiaEntity*>* getDrawEntities() const;	
	void addEntity(DiaEntity*);
	DiaEntity* findEntity(const CPoint& point) const;
	bool findConnected(const DiaEntity* entity, std::list<DiaEntity*>* ) const;
	bool selectEntity(const CPoint& );
	void clearDocument();	
	bool haveSelected() const;
	void clearSelection();
	void moveSelected(const std::pair<LONG,LONG>&);
	void deleteSelected();
	bool areAlreadyConnected(const DiaEntity*, const DiaEntity*) const;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCDiaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	std::list<DiaEntity*>		m_entities;	
	std::list<DiaEntity*>		m_selectedEntities;
	IDiaSaver*					m_saver;
	DiaBinarySaver				m_binarySaver;
	IDiaLoader*					m_loader;
	DiaBinaryLoader				m_binaryLoader;
};
