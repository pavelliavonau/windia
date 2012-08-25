#include "StdAfx.h"
#include "DiaBinaryLoader.h"
#include "DiaRectangle.h"
#include "DiaEllipse.h"
#include "DiaArrow.h"
#include "DiaTriangle.h"
#include <fstream>

DiaBinaryLoader::DiaBinaryLoader(void)
{
}


DiaBinaryLoader::~DiaBinaryLoader(void)
{
}

bool DiaBinaryLoader::loadEnities(LPCTSTR lpszPathName, std::vector<DiaEntity*>* entities) 
{
	std::fstream file(lpszPathName, std::ios_base::in|std::ios_base::binary);

	while(true)
	{					
		file.read(block.f_char, sizeof(block));
		if (file.eof())
			break;
		DiaEntity::Type type = static_cast<DiaEntity::Type>(block.f_int);
		switch (type)
		{
			case DiaEntity::Ellipse :	{ loadEllipse(file, entities); break; }
			case DiaEntity::Rectangle :	{ loadRectangle(file, entities); break; }
			case DiaEntity::Triangle :	{ loadTriangle(file, entities); break; }
			case DiaEntity::Arrow :		{ loadArrow(file, entities); break; }
			default: break;
		}			
	}

	file.close();

	return true;
}

bool DiaBinaryLoader::loadRectangle(std::fstream& fstream, std::vector<DiaEntity*>* entities)
{
	long id;
	int x1,y1,x2,y2;

	fstream.read(block.f_char, sizeof(block));
	id = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	x1 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	y1 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	x2 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	y2 = block.f_int;
		
	DiaRectangle* pRect = new DiaRectangle(x1, y1, x2, y2);
	entities->push_back(pRect);

	m_loaded.insert( std::pair<long,DiaEntity*>(id,pRect) );

	return true;
}

bool DiaBinaryLoader::loadTriangle(std::fstream& fstream, std::vector<DiaEntity*>* entities)
{
	long id;
	int xA,yA,xB,yB,xC,yC;

	fstream.read(block.f_char, sizeof(block));
	id = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	xA = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	yA = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	xB = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	yB = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	xC = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	yC = block.f_int;
		
	DiaTriangle* pTriangle = new DiaTriangle(xA, yA, xB, yB, xC, yC);
	entities->push_back(pTriangle);

	m_loaded.insert( std::pair<long,DiaEntity*>(id,pTriangle) );

	return true;
}

bool DiaBinaryLoader::loadEllipse(std::fstream& fstream, std::vector<DiaEntity*>* entities)
{
	long id;
	int x1,y1,x2,y2;

	fstream.read(block.f_char, sizeof(block));
	id = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	x1 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	y1 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	x2 = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	y2 = block.f_int;
		
	DiaEllipse* pEllipse = new DiaEllipse(x1, y1, x2, y2);
	entities->push_back(pEllipse);

	m_loaded.insert( std::pair<long,DiaEntity*>(id, pEllipse) );
	return true;
}

bool DiaBinaryLoader::loadArrow(std::fstream& fstream, std::vector<DiaEntity*>* entities)
{
	long id;
	int begin_id, end_id;

	fstream.read(block.f_char, sizeof(block));
	id = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	begin_id = block.f_int;

	fstream.read(block.f_char, sizeof(block));
	end_id = block.f_int;	
		
	std::vector<DiaEntity*> link;	
	
	DiaEntity* e;

	std::map<long, DiaEntity*>::iterator it = m_loaded.find(begin_id);
	e = (*it).second;
	link.push_back(e);

	it = m_loaded.find(end_id);
	e = (*it).second;
	link.push_back(e);

	DiaArrow* pArrow = new DiaArrow(link);
	entities->push_back(pArrow);

	m_loaded.insert( std::pair<long,DiaEntity*>(id,pArrow) );

	return true;
}