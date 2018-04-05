#pragma once
#include "CEntity.h"
class Ball
{
public:
	Ball(float x, float y, float radius);
	void Render();
	~Ball();
private:
	float x;
	float y;
	float radius;
};

