#pragma once
#include "CEntity.h"
#include "table.h"
class Flipper : public CEntityPolygon
{
public:
	Flipper(float x, float y, bool flipped);
	void CreateTable();
	void TransformTable();
	void Update(float deltaTime);
	void Render();
	~Flipper();
public:
	CTable table;
	float maxRotation = 0;
	float minRotation = -32;
	int flip = 1; // -1 == flipped
};

