#pragma once
#include <list>

class DiaEntity;

class IDiaLoader
{
public:
	IDiaLoader(void);
	virtual ~IDiaLoader(void);

	virtual bool loadEnities(LPCTSTR lpszPathName, std::list<DiaEntity*>* entities) = 0;
};

