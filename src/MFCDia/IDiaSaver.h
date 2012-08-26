#pragma once

#include <list>

class DiaEntity;

class IDiaSaver
{
public:
	IDiaSaver(void);
	virtual ~IDiaSaver(void);

	virtual bool saveEnities(LPCTSTR lpszPathName, const std::list<DiaEntity*>& entities) const = 0;

};

