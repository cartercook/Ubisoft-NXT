#pragma once
#include "CEntity.h"
#include "flipper.h"
#include "table.h"
class Ball : CEntity
{
public:
	Ball(float x, float y, float radius);
	void Update(float deltaTime);
	void Collide(CTable table, float bounceFactor = 1);
	void Collide(Flipper flipper);
	void Render();
	~Ball();
private:
	float radius;
};

