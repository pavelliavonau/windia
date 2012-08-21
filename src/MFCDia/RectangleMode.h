#pragma once
#include "abstractmode.h"

class CMFCDiaView;

class RectangleMode :
	public AbstractMode
{
public:
	RectangleMode(CMFCDiaView*);
	virtual ~RectangleMode(void);

	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;

protected:
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;	
};

