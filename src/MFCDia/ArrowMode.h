#pragma once
#include "abstractmode.h"

class CMFCDiaView;

class ArrowMode :
	public AbstractMode
{
public:
	ArrowMode(CMFCDiaView* parent);
	virtual ~ArrowMode(void);		
	
	bool isPreviewAvailable() const;
	void drawPreview(CDC* pDC) const;
	LPCTSTR getCurrentCursor() const;

	void OnLButtonDown(UINT Flags, CPoint Loc);
	void OnLButtonUp(UINT Flags, CPoint Loc);
	void OnMouseMove(UINT nFlags, CPoint point);

protected:

	bool isEnoughtItems() const;
	DiaEntity* createEntity() const;	
	virtual void tryCreateEntity();
};

