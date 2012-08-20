#pragma once
#include "abstractmode.h"
class HandMode :
	public AbstractMode
{
public:
	HandMode(void);
	virtual ~HandMode(void);
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;
	AbstractMode::modes getModeType() const;
};

