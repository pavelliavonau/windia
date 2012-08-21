#pragma once
#include "abstractmode.h"

class CMFCDiaView;

class TriangleMode :
	public AbstractMode
{
public:
	TriangleMode(CMFCDiaView*);
	virtual ~TriangleMode(void);

	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;

protected:
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;	
};

