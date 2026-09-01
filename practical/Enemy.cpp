#include "Enemy.h"
void Enemy::Move()
{
	bullet->SetPosition(Feet());
	if (movement >= maxVerticalMove || HitYBoundary()) {
		movement = 0;
		switch (current) {
		case UP:
			current = DOWN;
			break;
		case DOWN:
			current = UP;
			break;
		}
	}
	if (HitRightBoundary()) {
		position.x = windowWidth - sprite->width * transform->scaling.x;
	}
	else if (HitLeftBoundary()) {
		position.x = 0;
	}
	if (HitBottomBoundary()) {
		position.y = windowHeight - sprite->height * transform->scaling.y;

	}
	else if (HitTopBoundary()) {
		position.y = 0;
	}
	physics->AddForce(current);
	movement++;
	GameObject::Move();
	Shooter::MoveBullets();
}
void Enemy::Shoot() {
	Shooter::Shoot(Feet());
}

Enemy::Enemy(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* projectile, int cooldown, float maxHp)
	:GameObject(sprite, mass, power, posX, posY, maxHp),
	Shooter(projectile, cooldown)
{
	maxVerticalMove = 70;
	movement = 0;
	current = UP;
}
Enemy::Enemy(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY, Bullet* projectile, int cooldown, float maxHp):GameObject(sprite, mass, D3DXVECTOR2(horPower, verPower), D3DXVECTOR2(posX, posY), maxHp),
Shooter(projectile, cooldown)
{
	maxVerticalMove = 70;
	movement = 0;
	current = UP;
}
D3DXVECTOR2 Enemy::Ground() {
	return D3DXVECTOR2(windowWidth, windowHeight);
}
D3DXVECTOR2 Enemy::Feet() {
	return (position + D3DXVECTOR2(55, 70));
}
void Enemy::Reset() {
	sprite->state = 0;
	sprite->max = 8;
	gun.clear();
	GameObject::Reset();
}
void Enemy::Render() {
	bullet->Render();
	Shooter::Render();
	GameObject::Render();
}
void Enemy::CalculateAnimation() {
	if (hp <= 0) {
		sprite->current = 0;
		sprite->state = 1;
		sprite->max = 5;
	}
	if (current == 5) {
		render = false;
	}
	GameObject::CalculateAnimation();
}
RECT Enemy::CalculateHitBox() {
	hitbox.left = position.x + 11;
	hitbox.top = position.y + 96;
	hitbox.right = position.x + 11;
	hitbox.bottom = position.y + 109;
	return hitbox;
}

Enemy::Enemy(Enemy* enemy) :GameObject(enemy),Shooter(enemy)
{
	enemy->maxVerticalMove = maxVerticalMove;
	enemy->movement = 0;
	enemy->current = UP;
}
