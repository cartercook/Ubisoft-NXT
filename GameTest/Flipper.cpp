#include "stdafx.h"
//------------------------------------------------------------------------
#include "Flipper.h"
#include "table.h"
#include "app\app.h"

float points[] = {
	-10, 0,
	10, 10,
	52, 0,
	54, -4,
	32, -6,
	0, -10,
	-10, 0
};
const int pointsLength = 14;

Flipper::Flipper(float x, float y)
{
	position = CPoint();
	position.m_x = x;
	position.m_y = y;

	CreateTable();
}

void Flipper::CreateTable()
{
	for (int i = 2; i < pointsLength; i += 2)
	{
		CLineSegment line;
		line.m_type = eLine_Flipper;
		line.m_start.m_x = points[i - 2];
		line.m_start.m_y = points[i - 1];
		line.m_end.m_x = points[i];
		line.m_end.m_y = points[i + 1];
		table.m_lines.push_back(line);
	}
}

void Flipper::TransformTable(float x, float y, float rotation)
{
	float s = sin(rotation*PI / 180);
	float c = cos(rotation*PI / 180);

	for (int i = 2; i < pointsLength; i += 2)
	{
		CLineSegment &line = table.m_lines.at(i/2 - 1);

		float startX = points[i - 2];
		float startY = points[i - 1];
		float endX = points[i];
		float endY = points[i + 1];

		// rotate points by c,s and translate by x,y
		line.m_start.m_x = x + startX * c - startY * s;
		line.m_start.m_y = y + startX * s + startY * c;
		line.m_end.m_x = x + endX * c - endY * s;
		line.m_end.m_y = y + endX * s + endY * c;
	}
}

void Flipper::Update(float deltaTime)
{
	float rotationSpeed = 720 * (deltaTime / 1000);

	if (App::IsKeyPressed(VK_SPACE))
	{
		rotation += rotationSpeed;

		if (rotation > 32)
		{
			rotation = 32;
		}
	}
	else
	{
		rotation -= rotationSpeed;

		if (rotation < 0)
		{
			rotation = 0;
		}
	}

	TransformTable(position.m_x, position.m_y, rotation);
}

void Flipper::Render()
{
	table.Render();
}

Flipper::~Flipper()
{

}
