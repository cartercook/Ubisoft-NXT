#include "table.h"

#pragma once
class CEntity
{
public:
	CEntity(float x, float y, CTable table);
	void Render();
	~CEntity();
private:
	float x = 0;
	float y = 0;
	CTable table;
	int size;
};

