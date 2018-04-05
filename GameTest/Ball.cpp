#include "stdafx.h"
#include "Ball.h"
#include "app\app.h"


Ball::Ball(float x, float y, float radius)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}

void Ball::Render()
{
	App::DrawCircle(x, y, radius, 10, 1, 1, 1);
}

Ball::~Ball()
{

}