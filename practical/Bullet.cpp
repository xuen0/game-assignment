#include "Bullet.h"

Bullet::Bullet(Bullet* bullet) 
	:GameObject(bullet){}

Bullet* Bullet::Reload()
{
	return new Bullet(this);
}

void Bullet::Out()
{
	physics->AddForce(RIGHT);
}

Bullet::Bullet(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY) :GameObject(sprite, mass, D3DXVECTOR2(horPower, verPower), D3DXVECTOR2(posX, posY))
{}



