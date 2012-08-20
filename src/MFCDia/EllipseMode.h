#pragma once
#include "abstractmode.h"
class EllipseMode :
	public AbstractMode
{
public:
	EllipseMode(void);
	virtual ~EllipseMode(void);
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;
	AbstractMode::modes getModeType() const;
};

