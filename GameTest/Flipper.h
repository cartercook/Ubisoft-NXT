#pragma once
#include "CEntity.h"
#include "table.h"
class Flipper : CEntity
{
public:
	Flipper(float x, float y, CTable table);
	~Flipper();
public:
	CTable table;
};

