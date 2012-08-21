#pragma once
#include <vector>
#include "DiaEntity.h"

class AbstractMode
{
public:
	enum modes{
		RECTANGLE_MODE, HAND_MODE, ARROW_MODE, ELLIPSE_MODE, TRIANGLE_MODE
	};

	AbstractMode(void);
	virtual ~AbstractMode(void);
	void pushPoint(CPoint);
	CPoint pullPoint();
	void pushEntity(DiaEntity*);
	DiaEntity* pullEntity();
	const std::vector<CPoint>& getPoints();
	virtual bool isEnoughtItems() const = 0;
	virtual DiaEntity* createEntity() const = 0;
	virtual void resetMode();
	virtual bool isPreviewAvailable() const = 0;
	virtual void drawPreview(CDC* pDC) const = 0;
	virtual void setMousePos(CPoint);
	virtual LPCTSTR getCurrentCursor() const = 0;
	virtual modes getModeType() const = 0;

protected:
	std::vector<CPoint>		m_points;
	std::vector<DiaEntity*> m_entities;
	CPoint					m_mousePosition;
};

