#include "StdAfx.h"
#include "DiaArrow.h"
#include "Arrow.h"


DiaArrow::DiaArrow(std::list<DiaEntity*> link)
{
	m_connectionSequence = link;
}


DiaArrow::~DiaArrow(void)
{
}

void DiaArrow::draw(CDC* pDC) const
{

	if (m_selected)
	{		
		CPen* pOldPen = pDC->SelectObject(&m_penBlue);

		drawArrow(pDC);

		pDC->SelectObject(pOldPen);
	}
	else
		drawArrow(pDC);	
}

void DiaArrow::drawArrow(CDC* pDC) const
{
	DiaEntity* fromEntity = m_connectionSequence.front();
	DiaEntity* toEntity = m_connectionSequence.back();	

	CPoint fromCenter = fromEntity->getCentralPoint();
	CPoint toCenter = toEntity->getCentralPoint();

	CPoint pFrom = fromEntity->getCrossPoint( fromCenter, toCenter );
	CPoint pTo = toEntity->getCrossPoint( fromCenter, toCenter );

	if (fromEntity->contains(pTo)||
		toEntity->contains(pFrom))
	{
		return;
	}

	pDC->MoveTo(pFrom.x, pFrom.y);	

	ARROWSTRUCT arrow;
	arrow.bFill = false;
	arrow.fTheta = 3.14f / 6;
	arrow.nWidth = 10;

	ArrowTo(pDC->m_hDC, pTo.x, pTo.y, &arrow);
}

bool DiaArrow::contains(const CPoint& rpoint) const
{
	return false;
}

void DiaArrow::applyVec(const std::pair<LONG,LONG>& vec)
{
}

CPoint DiaArrow::getCentralPoint() const
{
	return CPoint();
}

CPoint DiaArrow::getCrossPoint(const CPoint& from, const CPoint& to) const
{
	return getCentralPoint();
}

const DiaEntity* DiaArrow::getBeginEntity() const
{
	return m_connectionSequence.front();
}
const DiaEntity* DiaArrow::getEndEntity() const
{
	return m_connectionSequence.back();
}