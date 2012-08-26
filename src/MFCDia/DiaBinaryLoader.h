#pragma once
#include "idialoader.h"
#include <list>
#include "BinaryTypes.h"
#include <map>

extern block_t block;

class DiaBinaryLoader :
	public IDiaLoader
{
public:
	DiaBinaryLoader(void);
	virtual ~DiaBinaryLoader(void);

	bool loadEnities(LPCTSTR lpszPathName, std::list<DiaEntity*>* entities) ;

private:

	std::map<long, DiaEntity*>	m_loaded;

	bool loadEllipse(std::fstream& rFile, std::list<DiaEntity*>* entities);
	bool loadRectangle(std::fstream& rFile, std::list<DiaEntity*>* entities);
	bool loadTriangle(std::fstream& rFile, std::list<DiaEntity*>* entities);
	bool loadArrow(std::fstream& rFile, std::list<DiaEntity*>* entities);
};

