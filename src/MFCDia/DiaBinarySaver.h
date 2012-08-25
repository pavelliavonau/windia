#pragma once
#include "idiasaver.h"

class DiaBinarySaver :
	public IDiaSaver
{
public:
	DiaBinarySaver();
	virtual ~DiaBinarySaver(void);

	bool saveEnities(LPCTSTR lpszPathName, const std::vector<DiaEntity*>& entities) const;

private:

	void saveEllipse(const DiaEntity* pEntity, std::fstream& rFile) const;
	void saveRectangle(const DiaEntity* pEntity, std::fstream& rFile) const;
	void saveTriangle(const DiaEntity* pEntity, std::fstream& rFile) const;
	void saveArrow(const DiaEntity* pEntity, std::fstream& rFile) const;
};