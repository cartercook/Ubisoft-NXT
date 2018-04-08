#include "stdafx.h"
#include "table.h"
#include "app\app.h"

CTable::CTable()
{
	m_lineDefs[eLine_Hard] = CLineDefinition("Hard", .8f, .6f, .2f);
	m_lineDefs[eLine_Soft] = CLineDefinition("Soft", .4f, .3f, .1f);
	m_lineDefs[eLine_Power] = CLineDefinition("Power", .2f, .2f, .6f);
	m_lineDefs[eLine_Flipper] = CLineDefinition("Flipper", .5f, .9f, .1f);
	m_lineDefs[eLine_Fail] = CLineDefinition("Fail", .8f, .3f, .9f);
	m_lineDefs[eLine_Score] = CLineDefinition("Score", .7f, .4f, .4f);
}

void CTable::Render()
{
	for (CLineSegment line : m_lines)
	{
		line.Render(m_lineDefs[line.m_type]);
	}
}

// https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
void CTable::Render(float x, float y, float rotation)
{
	float s = sin(rotation*PI / 180);
	float c = cos(rotation*PI / 180);

	for (CLineSegment line : m_lines)
	{
		// rotate points
		float startX = line.m_start.m_x * c - line.m_start.m_y * s;
		float startY = line.m_start.m_x * s + line.m_start.m_y * c;
		float endX = line.m_end.m_x * c - line.m_end.m_y * s;
		float endY = line.m_end.m_x * s + line.m_end.m_y * c;

		// get LineDefition
		CLineDefinition def = m_lineDefs[line.m_type];

		// translate point by (x,y)
		App::DrawLine(x + startX, y + startY, x + endX, y + endY, def.m_Red, def.m_Green, def.m_Blue);
	}
}

CLineSegment::CLineSegment() : CLineSegment(0.0f, 0.0f, 0.0f, 0.0f, eLine_Fail)
{
}

CLineSegment::CLineSegment(float x1, float y1, float x2, float y2, LineType type)
{
	m_start.m_x = x1;
	m_start.m_y = y1;
	m_start.m_selected = false;
	m_end.m_x = x2;
	m_end.m_y = y2;
	m_end.m_selected = false;
	m_type = type;
	m_selected = false;
}


float CLineSegment::DistanceToLine(float x, float y)
{
	return VectorToPoint(x, y).Length();
}

CVector CLineSegment::VectorToPoint(float x, float y)
{
	const float x0 = m_start.m_x;
	const float x1 = m_end.m_x;
	const float y0 = m_start.m_y;
	const float y1 = m_end.m_y;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float linelengthSquared = dx * dx + dy * dy;
	float param = ((x - x0)*dx + (y - y0)*dy) / linelengthSquared;
	if (param > 1)
		param = 1;
	if (param < 0)
		param = 0;

	float nearestX = x0 + param * dx;
	float nearestY = y0 + param * dy;

	return CVector(x - nearestX, y - nearestY);
}

/* float CLineSegment::DistanceToInfiniteLine(float x, float y)
{
	// See https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
	const float x0 = m_start.m_x;
	const float x1 = m_end.m_x;
	const float y0 = m_start.m_y;
	const float y1 = m_end.m_y;

	float numerator = abs((y1 - y0)*x - (x1 - x0)*y + x1*y0 - y1*x0);
	float denomenator = sqrt((y1 - y0)*(y1 - y0) + (x1 - x0)*(x1 - x0));
	float distance = numerator / denomenator;
	
	return distance;
} */

bool CLineSegment::IsOnLine(float x, float y, float tolerance)
{
	return DistanceToLine(x,y) < tolerance;
}

void CLineSegment::Render(CLineDefinition def)
{
	App::DrawLine(m_start.m_x, m_start.m_y, m_end.m_x, m_end.m_y, def.m_Red, def.m_Green, def.m_Blue);
}

float CPoint::DistanceToPoint(float x, float y)
{
	float dX = x - m_x;
	float dY = y - m_y;
	float distance = sqrt(dX*dX + dY*dY);

	return distance;
}

bool CPoint::IsOnPoint(float x, float y, float tolerance)
{
	return DistanceToPoint(x, y) < tolerance;
}

CLineDefinition::CLineDefinition(const char * name, float r, float g, float b)
{
	m_name = name;
	m_Red = r;
	m_Green = g;
	m_Red = b;
}

CVector::CVector(float x, float y)
{
	m_x = x;
	m_y = y;
}

float CVector::Length()
{
	return sqrt(m_x*m_x + m_y*m_y);
}

CVector CVector::Normalized()
{
	float length = Length();
	return CVector(m_x/length, m_y/length);
}

CVector CVector::operator*(float value)
{
	return CVector(m_x*value, m_y*value);
}

CVector CVector::operator-(CVector vector)
{
	return CVector(m_x - vector.m_x, m_y - vector.m_y);
}
