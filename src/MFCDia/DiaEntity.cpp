#include "StdAfx.h"
#include "DiaEntity.h"


DiaEntity::DiaEntity(void)
{
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
