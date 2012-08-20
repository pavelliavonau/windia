#pragma once
#include "abstractmode.h"
class ArrowMode :
	public AbstractMode
{
public:
	ArrowMode(void);
	virtual ~ArrowMode(void);
	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;
	AbstractMode::modes getModeType() const;
};

