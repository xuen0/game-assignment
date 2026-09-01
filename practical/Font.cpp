#include "Font.h"
#include <iostream>
using namespace std;

Font::Font(LPCSTR text,int height,int width,int weight,boolean italic, const char* fontType,
	int top, int bottom, int left, int right,int red,int green,int blue)
{
	HRESULT hr = D3DXCreateFont(d3dDevice, height, width, weight, 1, italic,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontType, &font);
	if (FAILED(hr)) {
		std::cout << "Failed to load texture" << std::endl;
		// return  some eror message
	}
	this->height = height;
	this->width = width;
	this->weight = weight;
	this->italic = italic;
	this->fontType = fontType;
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;
	color = D3DCOLOR_XRGB(red, green, blue);
	this->text = text;
	
}

void Font::CleanUp() {
	font->Release();
	font = NULL;
}

void Font::Render(){
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	spriteBrush->SetTransform(&matrix);
	font->DrawText(spriteBrush, text, -1, &rect,DT_CENTER,color );
}