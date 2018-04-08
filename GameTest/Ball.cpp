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

void Ball::Collide(CTable table)
{
	for (CLineSegment line : table.m_lines)
	{
		CVector vector = line.VectorToPoint(position.m_x, position.m_y);
		float overlap = radius - vector.Length();

		if (overlap >= 0)
		{
			CVector normalized = vector.Normalized();

			ApplyNormalForce(normalized, overlap);
		}
	}
}

int debug = -1;

void Ball::Collide(const CEntityPolygon *entity)
{
	//entity->table.m_lines.push_back(CLineSegment());
	//debug = entity->table.m_lines.size();

	for (CLineSegment line : entity->table.m_lines)
	{
		//looped = true;

		CVector vector = line.VectorToPoint(position.m_x, position.m_y);
		float overlap = radius - vector.Length();

		if (overlap >= 0)
		{
			CVector normalized = vector.Normalized();

			ApplyNormalForce(normalized, overlap);

			ApplyAngularImpulse(entity);
		}
	}
}

void Ball::ApplyNormalForce(CVector surfaceNormal, float overlap)
{
	CVector separationVector = surfaceNormal * overlap;
	position.m_x += separationVector.m_x;
	position.m_y += separationVector.m_y;

	// apply normal force
	// x component = m*g*cos(theta)
	// y component = m*g*sin(theta)
	// equal and opposite force
	acceleration.m_x -= (acceleration.m_x + acceleration.m_y) * surfaceNormal.m_x;
	acceleration.m_y -= (acceleration.m_x + acceleration.m_y) * surfaceNormal.m_y;
}

void Ball::ApplyAngularImpulse(const CEntityPolygon *entity)
{
	// apply (fake) collision torque
	// vector perpendicular to radius, scaled by distance from axis of rotation
	CPoint entityPosition = entity->position;
	CVector radiusVector = entityPosition - position;

	// rotate radiusVector 90 degrees clockwise
	CVector perpVector = CVector(radiusVector.m_y, -radiusVector.m_x);

	CVector force = perpVector.Normalized() * entity->angularVelocity * radiusVector.Length(); // force scaled by distance from point of rotation

	acceleration += force;
}

void Ball::Render()
{
	App::DrawCircle(position.m_x, position.m_y, radius, 25, 1, 1, 1);

	char buffer[256];
	snprintf(buffer, sizeof buffer, "%i,", debug);
	App::Print(0, 0, buffer);

	char buffer2[256];
	snprintf(buffer2, sizeof buffer2, "%f, %f", acceleration.m_x, acceleration.m_y);
	App::Print(0, 50, buffer2);
}

Ball::~Ball()
{

}