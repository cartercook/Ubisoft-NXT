#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------
#include "Ball.h"
#include "flipper.h"
#include "app\app.h"
//------------------------------------------------------------------------

const float gravity = -50;

CVector velocity = CVector(0, 0);
CVector acceleration = CVector(0, gravity);

Ball::Ball(float x, float y, float radius)
{
	position = CPoint(x, y);
	this->radius = radius;
}

void Ball::Update(float deltaTime)
{
	// update velocity
	velocity.m_x += acceleration.m_x * (deltaTime / 1000);
	velocity.m_y += acceleration.m_y * (deltaTime / 1000);

	// update position
	position.m_x += velocity.m_x * (deltaTime / 1000);
	position.m_y += velocity.m_y * (deltaTime / 1000);

	// reset accumulated forces from last frame
	acceleration.m_x = 0;
	acceleration.m_y = gravity;
}

void Ball::Collide(CTable table, float deltaTime)
{
	for (CLineSegment line : table.m_lines)
	{
		CPoint nearestPoint = line.NearestPoint(position.m_x, position.m_y);
		CVector vector = position - nearestPoint;
		float overlap = radius - vector.Length();

		if (overlap >= 0)
		{
			CVector normal = vector.Normalized();

			Separate(normal, overlap);

			ApplyNormalForce(nearestPoint, CPoint(0, 0), 0, deltaTime);
		}
	}
}

void Ball::Collide(CEntityPolygon *entity, CTable table, float deltaTime)
{
	for (CLineSegment line : table.m_lines)
	{
		CPoint nearestPoint = line.NearestPoint(position.m_x, position.m_y);
		CVector vector = position - nearestPoint;
		float overlap = radius - vector.Length();

		if (overlap >= 0)
		{
			CVector normal = vector.Normalized();

			Separate(normal, overlap);

			ApplyNormalForce(nearestPoint, entity->position, entity->angularVelocity, deltaTime);
		}
	}
}

void Ball::Separate(CVector surfaceNormal, float overlap)
{
	CVector separationVector = surfaceNormal * overlap;
	position.m_x += separationVector.m_x;
	position.m_y += separationVector.m_y;
}

void Ball::ApplyNormalForce(CPoint contactPoint, CPoint pointOfRotation, float angularVelocity, float deltaTime)
{
	float distFromAxis = (contactPoint - pointOfRotation).Length();
	float angularImpact = -50 * angularVelocity * distFromAxis * (deltaTime / 1000);

	CVector surfaceNormal = (position - contactPoint).Normalized();

	//velocity.m_x = velocity.m_x * surfaceNormal.m_y;
	//velocity.m_y = velocity.m_y * surfaceNormal.m_x;

	// x component = m*g*cos(theta)
	// y component = m*g*sin(theta)
	// equal and opposite force
	acceleration.m_x -= (acceleration.m_x + acceleration.m_y + angularImpact) * surfaceNormal.m_x;
	acceleration.m_y -= (acceleration.m_x + acceleration.m_y + angularImpact) * surfaceNormal.m_y;
}

void Ball::ApplyAngularImpulse(CEntityPolygon *entity, CPoint contactPoint)
{
	// apply fake collision torque
	// vector perpendicular to radius, scaled by distance from axis of rotation
	CVector radiusVector = entity->position - contactPoint;

	// rotate radiusVector 90 degrees clockwise
	CVector perpVector = CVector(radiusVector.m_y, -radiusVector.m_x);

	CVector force = perpVector.Normalized() * entity->angularVelocity*(PI/(180 * 5)) * radiusVector.Length(); // force scaled by distance from point of rotation

	acceleration += force;
}

void Ball::Render()
{
	App::DrawCircle(position.m_x, position.m_y, radius, 25, 1, 1, 1);

	char buffer[256];
	snprintf(buffer, sizeof buffer, "%f, %f", velocity.m_x, velocity.m_y);
	App::Print(0, 50, buffer);

	char buffer2[256];
	snprintf(buffer2, sizeof buffer2, "%f, %f", acceleration.m_x, acceleration.m_y);
	App::Print(0, 0, buffer2);
}

Ball::~Ball()
{

}