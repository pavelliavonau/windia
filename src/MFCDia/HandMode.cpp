#include "StdAfx.h"
#include "HandMode.h"


HandMode::HandMode(void)
{
}


HandMode::~HandMode(void)
{
}

bool HandMode::isEnoughtItems() const
{
	return false;
}

DiaEntity* HandMode::createEntity() const
{
	return NULL;		// WARNING: stub
}

bool HandMode::isPreviewAvailable() const
{
	return false;
}

void HandMode::drawPreview(CDC* pDC) const
{
}

LPCTSTR HandMode::getCurrentCursor() const
{
	return IDC_HAND;
}

AbstractMode::modes HandMode::getModeType() const
{
	return AbstractMode::HAND_MODE;
}