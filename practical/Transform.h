#pragma once
#include <d3dx9.h>
class Transform
{
public:
	float rotation;
	D3DXVECTOR2 rotationCenter = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 scalingCenter;
	D3DXVECTOR2 scaling;
	float scalingRotation;
	D3DXMATRIX matrix;
	Transform(int spriteWidth, int spriteHeight);
	void Scale(float x, float y);
	void Rotate(float rotation);
	D3DXMATRIX Matrix(D3DXVECTOR2 position);
};

