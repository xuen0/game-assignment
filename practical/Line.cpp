#include "Line.h"


void Line::Render() {
	line->SetWidth(width);
	line->Begin();
	line->Draw(lineVertices, 2, color);
	line->End();
}

Line::Line(int x1, int y1, int x2, int y2, int red, int green, int blue, float width) 
	:Line(x1,  y1,  x2,  y2,  red,  green,  blue,  width, 0)
{
	length = x2 - x1;
}

Line::Line(int x1, int y1, int x2, int y2, int red, int green, int blue, float width,float length) {
	lineVertices[0] = D3DXVECTOR2(x1, y1);
	lineVertices[1] = D3DXVECTOR2(x2, y2);
	this->color = D3DCOLOR_XRGB(red, green, blue);
	this->width = width;
	this->length = length;
}