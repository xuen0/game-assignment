#pragma once
#include <d3dx9.h>
#include "Globals.h"
#include "Direction.h"
class Physics
{
public:
	D3DXVECTOR2 velocity = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 acceleration = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 force = D3DXVECTOR2(0, 0);
	float mass;
	float friction;
	D3DXVECTOR2 power;
	Physics(float mass,float power);
	Physics(float mass, float verPower, float horPower);
	Physics(float mass, D3DXVECTOR2 power);
	void Move(D3DXVECTOR2* position);
	void AddForce(Direction direction);
};

