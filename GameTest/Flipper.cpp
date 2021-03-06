#include "stdafx.h"
//------------------------------------------------------------------------
#include "Flipper.h"
#include "table.h"
#include "app\app.h"

const float points[] = {
	-10, 0,
	10, 10,
	52, 0,
	54, -4,
	32, -6,
	0, -10,
	-10, 0
};
const int pointsLength = 14;

Flipper::Flipper(float x, float y, bool flipped)
{
	position = CPoint(x, y);
	rotation = minRotation;

	if (flipped)
	{
		flip = -1;
		
		float swap = minRotation;
		minRotation = 32;
		maxRotation = 0;
	}

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

void Flipper::TransformTable()
{
	float s = sin(rotation*PI / 180);
	float c = cos(rotation*PI / 180);

	for (int i = 2; i < pointsLength; i += 2)
	{
		CLineSegment &line = table.m_lines.at(i/2 - 1);

		float startX = points[i - 2] * flip;
		float startY = points[i - 1];
		float endX = points[i] * flip;
		float endY = points[i + 1];

		// rotate points by c,s and translate by x,y
		line.m_start.m_x = position.m_x + startX * c - startY * s;
		line.m_start.m_y = position.m_y + startX * s + startY * c;
		line.m_end.m_x = position.m_x + endX * c - endY * s;
		line.m_end.m_y = position.m_y + endX * s + endY * c;
	}
}

void Flipper::Update(float deltaTime)
{
	if (App::IsKeyPressed(VK_SPACE))
	{
		if (rotation < maxRotation)
		{
			angularVelocity = 720 * flip;
			rotation += angularVelocity * (deltaTime / 1000);
		}
		
		if (rotation >= maxRotation)
		{
			rotation = maxRotation;
			angularVelocity = 0;
		}
	}
	else
	{
		if (rotation > minRotation)
		{
			angularVelocity = -720 * flip;
			rotation += angularVelocity * (deltaTime / 1000);
		}

		if (rotation <= minRotation)
		{
			rotation = minRotation;
			angularVelocity = 0;
		}
	}

	TransformTable();
}

void Flipper::Render()
{
	table.Render();

	/*
	char buffer[256];
	snprintf(buffer, sizeof buffer, "%f", angularVelocity);
	App::Print(0, 0, buffer);
	*/
}

Flipper::~Flipper()
{

}
