#include "StdAfx.h"
#include "AbstractMode.h"


AbstractMode::AbstractMode(void)
{
}

AbstractMode::~AbstractMode(void)
{
}

void AbstractMode::pushPoint(CPoint new_point)
{
	m_points.push_back(new_point);
}

CPoint AbstractMode::pullPoint()
{
	CPoint point = m_points.back();
	m_points.pop_back();
	return point;
}

void AbstractMode::pushEntity(DiaEntity* pEntity)
{
	m_entities.push_back(pEntity);
}

DiaEntity* AbstractMode::pullEntity()
{
	DiaEntity* pEntity = m_entities.back();
	m_entities.pop_back();
	return pEntity;
}

const std::vector<CPoint>& AbstractMode::getPoints()
{
	return m_points;	
}

void AbstractMode::resetMode()
{
	m_points.clear();
	m_entities.clear();
}

void AbstractMode::setMousePos(CPoint new_point)
{
	m_mousePosition = new_point;
}