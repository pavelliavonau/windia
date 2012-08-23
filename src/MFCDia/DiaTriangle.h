#pragma once
#include "diaentity.h"
class DiaTriangle :
	public DiaEntity
{
public:
	DiaTriangle(LONG, LONG, LONG, LONG);
	virtual ~DiaTriangle(void);

	void draw(CDC* pDC) const;
	bool contains(const CPoint&) const;
	void applyVec(std::pair<LONG,LONG>&);
	CPoint getCentralPoint() const; 
	CPoint getCrossPoint(const CPoint& from, const CPoint& to) const;

private:

	int wherePoint(double ax, double ay, double bx, double by, double px, double py) const;
	void drawTriamgle(CDC* pDC) const;

	int m_xCenter;
	int m_yCenter;
	int m_xA;
	int m_yA;
	int m_xB;
	int m_yB;
	int m_xC;
	int m_yC;
};

