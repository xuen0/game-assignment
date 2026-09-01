#include "Physics.h"

Physics::Physics(float mass, float power) :Physics(mass, D3DXVECTOR2(power, power)){}

Physics::Physics(float mass, float verPower, float horPower):Physics(mass, D3DXVECTOR2(verPower,horPower)){}

Physics::Physics(float mass, D3DXVECTOR2 power)
{
	this->mass = mass;
	velocity = D3DXVECTOR2(0, 0);
	acceleration = D3DXVECTOR2(0, 0);
	force = D3DXVECTOR2(0, 0);
	friction = 0.9;
	this->power = power;
}

void Physics::Move(D3DXVECTOR2* position)
{
	acceleration = force / mass;
	velocity += acceleration;
	velocity *= friction;
	*position += velocity;
}
void Physics :: AddForce(Direction direction) {
	switch (direction)
	{
	case LEFT:
		force.x = -power.x;
		break;
	case RIGHT:
		force.x = power.x;
		break;
	case UP:
		force.y = -power.y;
		break;
	case DOWN:
		force.y = power.y;
		break;
	}
}