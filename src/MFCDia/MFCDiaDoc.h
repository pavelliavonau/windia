
// MFCDiaDoc.h : interface of the CMFCDiaDoc class
//


#pragma once
#include <vector>
#include "AbstractMode.h"

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
	const std::vector<DiaEntity*>* getDrawEntities() const;	
	void addEntity(DiaEntity*);
	DiaEntity* findEntity(const CPoint& point);
	void clearDocument();	

// Overrides
public:
	virtual BOOL OnNewDocument();
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
	std::vector<DiaEntity*>		m_entities;	
};
