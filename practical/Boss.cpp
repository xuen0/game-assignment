#include "Boss.h"

void Boss::Shoot() {
	if (hp < maxHp * 0.5 && babyCount < maxChildren) {
		if(Shooter::Shoot(Feet())) babyCount++;
	}
}

Boss::Boss(Sprite* sprite, float mass, float power, int posX, int posY, BabyEnemy* projectile, int cooldown, float maxHp)
	:GameObject(sprite, mass, power, posX, posY,maxHp),Shooter(projectile, cooldown),Enemy(sprite, mass, power, posX, posY, projectile, cooldown, maxHp)
{
	babyCount = 0;
	maxChildren = 4;
}
D3DXVECTOR2 Boss::Feet() {
	return (position + D3DXVECTOR2(55*transform->scaling.x, 70 * transform->scaling.y));
}
RECT Boss :: CalculateHitBox() {
	colWidth = sprite->width * transform->scaling.x * 0.8;
	colHeight = sprite->height * transform->scaling.y * 0.8;
	colXOffset = (sprite->width - colWidth) / 2;
	colYOffset = (sprite->height - colHeight) / 2;
	hitbox.left = position.x-50;
	hitbox.right = position.x + 45 * transform->scaling.x;
	hitbox.top = position.y;
	hitbox.bottom = position.y + 109 * transform->scaling.y *0.5;
	return hitbox;
}