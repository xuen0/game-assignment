#pragma once
#include "Globals.h"

class Font
{
public:
	LPD3DXFONT font = NULL;
	RECT rect;
	int height = 0;
	int width = 0;
	int weight = 0;
	boolean italic = false;
	const char* fontType = "Arial";
	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DCOLOR color;
	LPCSTR text;

	Font(LPCSTR text,int height, int width, int weight, boolean italic, const char* fontType,
		int top, int bottom, int left, int right, int red, int green, int blue);
	void Render();
	void CleanUp();
	
};
