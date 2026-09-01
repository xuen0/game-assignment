#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Globals.h"
class Sprite
{
public:
	LPDIRECT3DTEXTURE9 texture = NULL;
	RECT rect;
	int fileWidth = 0;
	int fileHeight = 0;
	int width = 0;
	int height = 0;
	int row = 0;
	int column = 0;
	int current = 0;
	int max = 0;
	int state = 0;
	D3DCOLOR color;
	int redFrame;
	Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int row, int column, int max, int startingState);
	Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int width, int height);
	Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int width, int height,int max, int row, int column);
	Sprite(LPDIRECT3DTEXTURE9* texture, Sprite* sprite);
	Sprite(Sprite* sprite);
	void CalculateRect(int state);
	void CalculateRect();
	void NextFrame();
	void Render(D3DXMATRIX matrix);
	void Render(D3DXVECTOR2 position);
	void Render(int posX, int posY);
	void Render();
	void CleanUp();
	void Red();
};

