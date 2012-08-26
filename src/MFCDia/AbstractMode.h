#pragma once
#include <vector>
#include <list>
#include "DiaEntity.h"

class CMFCDiaView;

class AbstractMode
{
public:	

	AbstractMode(void);
	virtual ~AbstractMode(void);

	virtual bool isPreviewAvailable() const = 0;
	virtual void drawPreview(CDC* pDC) const = 0;
	virtual LPCTSTR getCurrentCursor() const = 0;

	virtual void OnRButtonDown(UINT Flags, CPoint Loc);
	virtual void OnLButtonDown(UINT Flags, CPoint Loc);
	virtual void OnLButtonUp(UINT Flags, CPoint Loc);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

protected:

	void pushPoint(CPoint);
	CPoint pullPoint();
	void pushEntity(DiaEntity*);
	DiaEntity* pullEntity();
	const std::vector<CPoint>& getPoints();
	virtual bool isEnoughtItems() const = 0;
	virtual DiaEntity* createEntity() const = 0;
	virtual void resetMode();	
	virtual void setMousePos(CPoint);	
	virtual void tryCreateEntity();

	std::vector<CPoint>		m_points;
	std::list<DiaEntity*>	m_entities;
	CPoint					m_mousePosition;
	CMFCDiaView*			mp_parentView;	
};

