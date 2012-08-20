#pragma once
#include "abstractmode.h"
class RectangleMode :
	public AbstractMode
{
public:
	RectangleMode(void);
	virtual ~RectangleMode(void);
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;
	AbstractMode::modes getModeType() const;
};

