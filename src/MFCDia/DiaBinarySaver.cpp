#include "StdAfx.h"
#include "DiaBinarySaver.h"
#include "DiaEntity.h"
#include "DiaRectangle.h"
#include "DiaArrow.h"
#include "DiaEllipse.h"
#include "DiaTriangle.h"
#include <fstream>
#include "BinaryTypes.h"

block_t block;

DiaBinarySaver::DiaBinarySaver()
{	
}


DiaBinarySaver::~DiaBinarySaver(void)
{
}

bool DiaBinarySaver::saveEnities(LPCTSTR lpszPathName, const std::vector<DiaEntity*>& entities) const
{
	std::fstream file(lpszPathName, std::ios_base::out|std::ios_base::binary);

	for (std::vector<DiaEntity*>::const_iterator it = entities.cbegin() ; it != entities.cend(); it++)
	{
		const DiaEntity* e = *it;	
		DiaEntity::Type type = e->type();

		switch (type)
		{
			case DiaEntity::Ellipse :	{ saveEllipse(e, file); break; }
			case DiaEntity::Rectangle :	{ saveRectangle(e, file); break; }
			case DiaEntity::Triangle :	{ saveTriangle(e, file); break; }
			case DiaEntity::Arrow :		{ saveArrow(e, file); break; }
			default: break;
		}		
	}

	file.close();

	return true;
}

void DiaBinarySaver::saveEllipse(const DiaEntity* pEntity, std::fstream& fstream) const
{
	const DiaEllipse* pEllipse = dynamic_cast<const DiaEllipse*>(pEntity);	

	block.f_int = DiaEntity::Ellipse;
	fstream.write(block.f_char, sizeof(block));
	
	block.f_int = pEllipse->id();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pEllipse->getX1r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pEllipse->getY1r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pEllipse->getX2r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pEllipse->getY2r();
	fstream.write(block.f_char, sizeof(block));		
}

void DiaBinarySaver::saveRectangle(const DiaEntity* pEntity, std::fstream& fstream) const
{
	const DiaRectangle* pRect = dynamic_cast<const DiaRectangle*>(pEntity);	

	block.f_int = DiaEntity::Rectangle;
	fstream.write(block.f_char, sizeof(block));
	
	block.f_int = pRect->id();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pRect->getX1r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pRect->getY1r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pRect->getX2r();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pRect->getY2r();
	fstream.write(block.f_char, sizeof(block));			
	
}

void DiaBinarySaver::saveTriangle(const DiaEntity* pEntity, std::fstream& fstream) const
{
	const DiaTriangle* pTriangle = dynamic_cast<const DiaTriangle*>(pEntity);	

	block.f_int = DiaEntity::Rectangle;
	fstream.write(block.f_char, sizeof(block));
	
	block.f_int = pTriangle->id();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pTriangle->getXAr();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pTriangle->getYAr();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pTriangle->getXBr();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pTriangle->getYBr();
	fstream.write(block.f_char, sizeof(block));	

	block.f_int = pTriangle->getXCr();
	fstream.write(block.f_char, sizeof(block));	

	block.f_int = pTriangle->getYCr();
	fstream.write(block.f_char, sizeof(block));	

}

void DiaBinarySaver::saveArrow(const DiaEntity* pEntity, std::fstream& fstream) const
{
	const DiaArrow* pArrow = dynamic_cast<const DiaArrow*>(pEntity);	

	block.f_int = DiaEntity::Arrow;
	fstream.write(block.f_char, sizeof(block));
	
	block.f_int = pArrow->id();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pArrow->getBeginEntity()->id();
	fstream.write(block.f_char, sizeof(block));

	block.f_int = pArrow->getEndEntity()->id();
	fstream.write(block.f_char, sizeof(block));

}