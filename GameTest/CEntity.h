#pragma once
#include "table.h"
class CEntity
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
public:
	CPoint position;
};

