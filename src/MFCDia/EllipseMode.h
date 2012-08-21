#pragma once
#include "abstractmode.h"

class CMFCDiaView;

class EllipseMode :
	public AbstractMode
{
public:
	EllipseMode(CMFCDiaView* parent);
	virtual ~EllipseMode(void);

	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;

protected:
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;	
};

