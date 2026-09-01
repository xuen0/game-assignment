#include "Sprite.h"
#include <iostream>
#include "Globals.h"
using namespace std;
Sprite::Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int row, int column, int max, int startingState) {
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, fileName, &texture);
	if (FAILED(hr)) {
		std::cout << "Failed to load texture" << std::endl;
		// return  some eror message
	}
	this->fileWidth = fileWidth;
	this->fileHeight = fileHeight;
	this->row = row;
	this->column = column;
	width = fileWidth / column;
	height = fileHeight / row;
	current = 0;
	this->max = max;
	state = startingState;
	color = D3DCOLOR_XRGB(255, 255, 255);
	CalculateRect(startingState);
}
Sprite::Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int width, int height)
	:Sprite(fileName,fileWidth,fileHeight, width, height, 1, 1, 1){}
Sprite::Sprite(LPCSTR fileName, int fileWidth, int fileHeight, int width, int height, int max, int row, int column)
	:Sprite(fileName, fileWidth, fileHeight, row, column, max, 0) {
	this->width = width;
	this->height = height;
	color = D3DCOLOR_XRGB(255, 255, 255);
}
Sprite::Sprite(LPDIRECT3DTEXTURE9* texture, Sprite* sprite) {
// copy sprite
	this->texture = *texture;
	fileWidth = sprite->fileWidth;
	fileHeight = sprite->fileHeight;
	width = sprite->width;
	height = sprite->height;
	row = sprite->row;
	column = sprite->column;
	current = sprite->current;
	max = sprite->max;
	state = sprite->state;
	color = D3DCOLOR_XRGB(255, 255, 255);
}
Sprite::Sprite(Sprite* sprite)
{
	texture = sprite->texture;
	fileWidth = sprite->fileWidth;
	fileHeight = sprite->fileHeight;
	width = sprite->width;
	height = sprite->height;
	row = sprite->row;
	column = sprite->column;
	current = sprite->current;
	max = sprite->max;
	state = sprite->state;
	color = sprite->color;
}
void Sprite::CalculateRect(int state)
{
	rect.left = int(current % column) * width;
	rect.right = rect.left + width;
	rect.top = state * height;
	rect.bottom = rect.top + height;
}
void Sprite::CalculateRect()
{
	rect.left = int(current % column) * width;
	rect.right = rect.left + width;
	rect.top = int(current / column) * height;
	rect.bottom = rect.top + height;
}
void Sprite::NextFrame() {
	current++;
	if (current >= max) {
		current = 0;
	}
}
void Sprite::Render(D3DXMATRIX matrix)
{
	if (frame - redFrame >= 6) {
		redFrame = frame;
		color = D3DCOLOR_XRGB(255, 255, 255);
	}
	if (state != -1)CalculateRect(state);
	else CalculateRect();
	spriteBrush->SetTransform(&matrix);
	spriteBrush->Draw(texture, &rect, NULL, NULL,color);	
}

void Sprite::Render(D3DXVECTOR2 position)
{
	D3DXVECTOR3 positionv3 = D3DXVECTOR3(position.x, position.y, 0);
	CalculateRect();
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	spriteBrush->SetTransform(&matrix);
	spriteBrush->Draw(texture, &rect, NULL, &positionv3, color);
}
void Sprite::Render(int posX, int posY)
{
	Render(D3DXVECTOR2(posX, posY));
}
void Sprite::Render()
{
	Render(0, 0);
}
void Sprite::CleanUp()
{
	texture->Release();
	texture = NULL;
}

void Sprite::Red() {
	color = D3DCOLOR_XRGB(255, 0, 0);
	redFrame = frame;
}