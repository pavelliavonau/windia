#pragma once
#include <vector>

class DiaEntity;

class IDiaLoader
{
public:
	IDiaLoader(void);
	virtual ~IDiaLoader(void);

	virtual bool loadEnities(LPCTSTR lpszPathName, std::vector<DiaEntity*>* entities) = 0;
};

