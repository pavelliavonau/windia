#pragma once
#include "diaentity.h"


class DiaRectangle :
	public DiaEntity
{
public:
	DiaRectangle(int x1, int y1, int x2, int y2);
	virtual ~DiaRectangle(void);
	void draw(CDC* pDC);
	bool contains(const CPoint&);
	void applyVec(std::pair<LONG,LONG>&);
	CPoint getCentralPoint(); 

private:
	int m_x1;
	int m_y1;
	int m_x2;
	int m_y2;
};

