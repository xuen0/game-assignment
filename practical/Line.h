#pragma once
#include "Globals.h"

class Line
{
public:
	D3DXVECTOR2 lineVertices[2];
	D3DCOLOR color;
	float width;
	float length;
	void Render();
	Line(int x1, int y1, int x2, int y2, int red, int green, int blu, float width);
	Line(int x1, int y1, int x2, int y2, int red, int green, int blu, float width, float length);
};
