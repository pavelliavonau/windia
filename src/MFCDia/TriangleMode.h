#pragma once
#include "abstractmode.h"
class TriangleMode :
	public AbstractMode
{
public:
	TriangleMode(void);
	virtual ~TriangleMode(void);
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;
	AbstractMode::modes getModeType() const;
};

