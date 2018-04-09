#pragma once
#include "CEntity.h"
#include "flipper.h"
#include "table.h"
class Ball : public CEntity
{
public:
	Ball(float x, float y, float radius);
	void Update(float deltaTime);
	void Collide(CTable table, float deltaTime);
	void Collide(CEntityPolygon *entity, CTable table, float deltaTime);
	void Separate(CVector surfaceNormal, float overlap);
	void ApplyNormalForce(CPoint contactPoint, CPoint pointOfRotation, float angularVelocity, float deltaTime);
	void ApplyAngularImpulse(CEntityPolygon * entity, CPoint contactPoint);
	void Render();
	~Ball();
private:
	float radius;
};

