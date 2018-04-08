#pragma once
#include "CEntity.h"
#include "table.h"
class Flipper : CEntityPolygon
{
public:
	Flipper(float x, float y);
	void CreateTable();
	void TransformTable(float x, float y, float rotation);
	void Update(float deltaTime);
	void Render();
	~Flipper();
public:
	CTable table;
};

