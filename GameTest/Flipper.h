#pragma once
#include "CEntity.h"
#include "table.h"
class Flipper : public CEntityPolygon
{
public:
	Flipper(float x, float y);
	void CreateTable();
	void TransformTable();
	void Update(float deltaTime);
	void Render();
	~Flipper();
public:
	CTable table;
};

