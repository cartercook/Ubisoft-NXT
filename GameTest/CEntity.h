#pragma once
#include "table.h"
class CEntity
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
public:
	CPoint position;
};

class CEntityPolygon : public CEntity
{
public:
	float rotation = 0;
	float angularVelocity = 0;
	CTable table;
};