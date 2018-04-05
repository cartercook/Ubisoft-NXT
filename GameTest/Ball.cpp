#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Ball.h"
#include "app\app.h"
//------------------------------------------------------------------------

CVector velocity = CVector(0, 0);

Ball::Ball(float x, float y, float radius)
{
	position = CPoint();
	position.m_x = x;
	position.m_y = y;
	this->radius = radius;
}

void Ball::Update(float deltaTime)
{
	// gravity
	velocity.m_y -= deltaTime / 1000;

	//update position
	position.m_x += velocity.m_x;
	position.m_y += velocity.m_y;

	char buffer[64];
	snprintf(buffer, sizeof buffer, "%f", position.m_y);

	App::Print(0, 0, buffer);
}

void Ball::Collide(CTable table)
{
	for (CLineSegment line : table.m_lines)
	{
		CVector vector = line.VectorToPoint(position.m_x, position.m_y);
		
		float overlap = radius - vector.Length();
		if (overlap >= 0)
		{
			CVector separationVector = vector.Normalized() * overlap;
			position.m_x += separationVector.m_x;
			position.m_y += separationVector.m_y;
		}
	}
}

void Ball::Render()
{
	App::DrawCircle(position.m_x, position.m_y, radius, 25, 1, 1, 1);
}

Ball::~Ball()
{

}