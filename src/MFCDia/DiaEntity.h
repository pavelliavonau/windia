#pragma once
#include <afxwin.h>
#include <utility>
#include <stdint.h>

class DiaEntity
{
public:

	enum Type {
		Ellipse, Rectangle, Triangle, Arrow
	};

	DiaEntity(void);
	virtual ~DiaEntity(void);

	virtual void draw(CDC* pDC) const = 0;	
	virtual bool contains(const CPoint&) const = 0;
	void setSelected(bool);
	virtual bool isSelected() const;
	virtual void applyVec(std::pair<LONG,LONG>&) = 0;
	virtual CPoint getCentralPoint() const = 0;
	virtual CPoint getCrossPoint(const CPoint&, const CPoint&) const = 0;
	virtual DiaEntity::Type type() const = 0;

	uint32_t id() const
    {
        return reinterpret_cast<uint32_t>(this);
    }

protected:
	bool		m_selected;
	static CPen m_penBlue;

	// (C) http://users.livejournal.com/_winnie/152327.html
	bool lineIntersection(CPoint start1, CPoint end1, CPoint start2, CPoint end2, CPoint *out_intersection) const;	

};

