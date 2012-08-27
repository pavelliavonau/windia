#include "StdAfx.h"
#include "DiaEntity.h"


CPen DiaEntity::m_penBlue = CPen(PS_SOLID, 5, RGB(0, 0, 255));

DiaEntity::DiaEntity(void)
{	
	m_selected = false;
}


DiaEntity::~DiaEntity(void)
{
}

void DiaEntity::setSelected(bool value)
{
	m_selected = value;
}

bool DiaEntity::isSelected() const
{
	return m_selected;
}

bool DiaEntity::lineIntersection(const CPoint& start1, const CPoint& end1, const CPoint& start2, const CPoint& end2, CPoint *out_intersection) const
{
    CPoint dir1 = end1 - start1;
    CPoint dir2 = end2 - start2;

    //считаем уравнения прямых проходящих через отрезки
    float a1 = -dir1.y;
    float b1 = +dir1.x;
    float d1 = -(a1*start1.x + b1*start1.y);

    float a2 = -dir2.y;
    float b2 = +dir2.x;
    float d2 = -(a2*start2.x + b2*start2.y);

    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    float seg1_line2_start = a2*start1.x + b2*start1.y + d2;
    float seg1_line2_end = a2*end1.x + b2*end1.y + d2;

    float seg2_line1_start = a1*start2.x + b1*start2.y + d1;
    float seg2_line1_end = a1*end2.x + b1*end2.y + d1;

    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0) 
        return false;

    float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
    *out_intersection =  start1 + CPoint(u*dir1.x,u*dir1.y);

	return true;		
}