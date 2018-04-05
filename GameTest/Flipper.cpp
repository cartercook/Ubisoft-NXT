#include "stdafx.h"
#include "Flipper.h"
#include "table.h"

Flipper::Flipper(float x, float y, CTable table)
{
	position = CPoint();
	position.m_x = x;
	position.m_y = y;
	this->table = table;
}


Flipper::~Flipper()
{

}
