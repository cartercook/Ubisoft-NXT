#include <vector>
#pragma once

enum LineType
{
	eLine_Hard = 0,
	eLine_Soft,
	eLine_Power,
	eLine_Flipper,
	eLine_Fail,
	eLine_Score,
	eLine_END
};

class CVector
{
public:
	CVector(float x, float y);
	float Length();
	CVector Normalized();
	CVector operator*(float value);
	CVector operator+(CVector vector);
	void operator+=(CVector vector);
public:
	float m_x;
	float m_y;
};

class CPoint
{
public:
	CPoint();
	CPoint(float x, float y);
	float DistanceToPoint(float x, float y);
	bool IsOnPoint(float x, float y, float tolerance);
	CVector operator-(CPoint vector);
public:
	float m_x;
	float m_y;
	bool m_selected;
};

class CLineDefinition
{
public:
	CLineDefinition() {};
	CLineDefinition(const char* name, float r, float g, float b);
public:
	float m_Red;
	float m_Green;
	float m_Blue;
	const char* m_name;
};

class CLineSegment
{
public:
	CLineSegment();
	CLineSegment(float x1, float y1, float x2, float y2, LineType type);
	float DistanceToLine(float x, float y);
	CVector VectorToPoint(float x, float y);
	CPoint NearestPoint(float x, float y);
	bool IsOnLine(float x, float y, float tolerance = 5.0f);
	void Render(CLineDefinition def);
public:
	CPoint m_start;
	CPoint m_end;
	LineType m_type;
	bool m_selected;
};

// To hold a set of lines describing the background for the game
class CTable
{
public:
	CTable();
	void Render();
	void Render(float x, float y, float rotation);
public:
	std::vector<CLineSegment> m_lines;
	CLineDefinition m_lineDefs[eLine_END];
};



