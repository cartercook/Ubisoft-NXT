#include "stdafx.h"
//------------------------------------------------------------------------
#include <iostream>
//------------------------------------------------------------------------
#include "CEntity.h"
#include "app\app.h"



// First thing I want to implement is passing arrays of points into an object and rendering them offset by position
CEntity::CEntity(float x, float y, CTable table)
{
	this->x = x;
	this->y = y;
	this->table = table;
	this->size = size;
}

void CEntity::Render()
{
	table.Render();
}


CEntity::~CEntity()
{
}
