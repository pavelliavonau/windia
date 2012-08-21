#pragma once
#include <afxwin.h>
#include <utility>

class DiaEntity
{
public:
	DiaEntity(void);
	virtual ~DiaEntity(void);

	virtual void draw(CDC* pDC) const = 0;	
	virtual bool contains(const CPoint&) const = 0;
	void setSelected(bool);
	virtual bool isSelected() const;
	virtual void applyVec(std::pair<LONG,LONG>&) = 0;
	virtual CPoint getCentralPoint() const = 0;

protected:
	bool m_selected;

};

