#pragma once
#include "CEntity.h"
#include "table.h"
class Ball : CEntity
{
public:
	Ball(float x, float y, float radius);
	void Update(float deltaTime);
	void Collide(CTable table);
	void Render();
	~Ball();
private:
	float radius;
};

