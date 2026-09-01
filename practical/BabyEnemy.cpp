#include "BabyEnemy.h"
void BabyEnemy::Move()
{
	bullet->SetPosition(Feet());
	Shoot();
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
	if (movement == maxHorizontalMove) {
		physics->force.x = 0;
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
void BabyEnemy::Shoot() {
	Shooter::Shoot(Feet());
}
BabyEnemy::BabyEnemy(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY, Bullet* projectile, int cooldown, float maxHp)
	:Bullet(sprite, mass, D3DXVECTOR2(horPower, verPower), D3DXVECTOR2(posX, posY), maxHp),
	Shooter(projectile, cooldown)
{}
BabyEnemy::BabyEnemy(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* projectile, int cooldown, float maxHp)
	:Bullet(sprite, mass, power, posX, posY, maxHp),
	Shooter(projectile, cooldown)
{}
D3DXVECTOR2 BabyEnemy::Feet() {
	return (position + D3DXVECTOR2(55, 70));
}
void BabyEnemy::Render() {
	bullet->Render();
	Shooter::Render();
	GameObject::Render();
}
Bullet* BabyEnemy::Reload()
{
	return new BabyEnemy(this);
}
BabyEnemy::BabyEnemy(BabyEnemy* enemy) :Bullet(enemy), Shooter(enemy->bullet->Reload(), enemy->cooldown) {
	maxHorizontalMove = rand() % 10 + 8;
	maxVerticalMove = 70;
	movement = 0;
	current = UP;
}
void BabyEnemy::Out()
{
	physics->AddForce(LEFT);
}
RECT BabyEnemy::CalculateHitbox() {
	hitbox.left = position.x + 11;
	hitbox.top = position.y + 96;
	hitbox.right = position.x + 11;
	hitbox.bottom = position.y + 109;
	return hitbox;
}
void BabyEnemy::CalculateAnimation() {
	if (current == 5) {
		render = false;
	}
	GameObject::CalculateAnimation();
}