#pragma once
#include "diaentity.h"
class DiaTriangle :
	public DiaEntity
{
public:
	DiaTriangle(LONG centerX, LONG centerY, LONG radiusX, LONG radiusY);
	DiaTriangle(LONG xA, LONG yA, LONG xB, LONG yB, LONG xC, LONG yC);
	virtual ~DiaTriangle(void);

	void draw(CDC* pDC) const;
	bool contains(const CPoint&) const;
	void applyVec(const std::pair<LONG,LONG>&);
	CPoint getCentralPoint() const; 
	CPoint getCrossPoint(const CPoint& from, const CPoint& to) const;
	virtual DiaEntity::Type type() const { return DiaEntity::Triangle; };

	const int& getXAr() const { return m_xA; }
	const int& getYAr() const { return m_yA; }
	const int& getXBr() const { return m_xB; }
	const int& getYBr() const { return m_yB; }
	const int& getXCr() const { return m_xC; }
	const int& getYCr() const { return m_yC; }

private:

	int wherePoint(double ax, double ay, double bx, double by, double px, double py) const;
	void drawTriamgle(CDC* pDC) const;

	int m_radius;
	int m_xCenter;
	int m_yCenter;
	int m_xA;
	int m_yA;
	int m_xB;
	int m_yB;
	int m_xC;
	int m_yC;
};

