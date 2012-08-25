#pragma once

#include <vector>

class DiaEntity;

class IDiaSaver
{
public:
	IDiaSaver(void);
	virtual ~IDiaSaver(void);

	virtual bool saveEnities(LPCTSTR lpszPathName, const std::vector<DiaEntity*>& entities) const = 0;

};

