#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Ball.h"
#include "flipper.h"
#include "app\app.h"
//------------------------------------------------------------------------

CVector velocity = CVector(0, 0);
CVector acceleration = CVector(0, -1); //gravity

Ball::Ball(float x, float y, float radius)
{
	position = CPoint();
	position.m_x = x;
	position.m_y = y;
	this->radius = radius;
}

void Ball::Update(float deltaTime)
{
	// update velocity
	velocity.m_x += acceleration.m_x * (deltaTime / 1000);
	velocity.m_y += acceleration.m_y * (deltaTime / 1000);

	// update position
	position.m_x += velocity.m_x;
	position.m_y += velocity.m_y;

	// reset accumulated forces from last frame
	acceleration.m_x = 0;
	acceleration.m_y = -1; //gravity
}

void Ball::Collide(CTable table, const float bounceFactor)
{
	for (CLineSegment line : table.m_lines)
	{
		CVector vector = line.VectorToPoint(position.m_x, position.m_y);
		
		float overlap = radius - vector.Length();
		if (overlap >= 0)
		{
			CVector normalized = vector.Normalized();
			CVector separationVector = normalized * overlap;
			position.m_x += separationVector.m_x;
			position.m_y += separationVector.m_y;

			// apply normal force
			// x component = m*g*cos(theta)
			// y component = m*g*sin(theta)
			// equal and opposite force
			acceleration.m_x -= (acceleration.m_x + acceleration.m_y) * normalized.m_x * bounceFactor;
			acceleration.m_y -= (acceleration.m_x + acceleration.m_y) * normalized.m_y * bounceFactor;

			// apply collision torque
			// vector perpendicular to radius, scaled by distance from axis of rotation

			// float dist = position
			acceleration.m_x += 
		}
	}
}

void Ball::Collide(Flipper flipper)
{
	Collide(flipper.table);


}

void Ball::Render()
{
	App::DrawCircle(position.m_x, position.m_y, radius, 25, 1, 1, 1);

	char buffer[256];
	snprintf(buffer, sizeof buffer, "%f, %f", velocity.m_x, velocity.m_y);
	App::Print(0, 0, buffer);

	char buffer2[256];
	snprintf(buffer2, sizeof buffer2, "%f, %f", acceleration.m_x, acceleration.m_y);
	App::Print(0, 50, buffer2);
}

Ball::~Ball()
{

}