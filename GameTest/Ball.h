#pragma once
#include "CEntity.h"
#include "flipper.h"
#include "table.h"
class Ball : public CEntity
{
public:
	Ball(float x, float y, float radius);
	void Update(float deltaTime);
	void Collide(CTable table);
	void Collide(const CEntityPolygon *entity);
	void ApplyNormalForce(CVector surfaceNormal, float overlap);
	void ApplyAngularImpulse(const CEntityPolygon * entity);
	void Render();
	~Ball();
private:
	float radius;
};

