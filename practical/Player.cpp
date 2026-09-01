#include "Player.h"

Player::Player(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* bullet, int cooldown, float hp)
	:Shooter(bullet, cooldown), 
	GameObject(sprite, mass, power, posX, posY ,hp) {}
void Player::Move() {
	GameObject::Move();
	if (HitTopBoundary()) {
		position.y = 0;
	}
	else if (HitBottomBoundary()) {
		position.y = windowHeight - sprite->height;
	}
	if (HitLeftBoundary()) {
		position.x = 0;
	}
	else if (HitRightBoundary()) {
		position.x = windowWidth - sprite->width;
	}
	Shooter::MoveBullets();
}
void Player::Render()
{
	Shooter::Render();
	GameObject::Render();
}
void Player::Shoot() {
	Shooter::Shoot(PlaneHead());
}
void Player::ChangeDirection(Direction direction)
{
	switch (direction) {
	case UP:
		sprite->state = 2;
		sprite->current = 1;
		sprite->max = 2;
		break;
	case DOWN:
		sprite->state = 1;
		sprite->current = 1;
		sprite->max = 2;
		break;
	}
	physics->AddForce(direction);
}
void Player :: CalculateAnimation() {
	GameObject::CalculateAnimation();
	if (physics->force.y != 0) {
		sprite->current = 1;
	}
	else {
		sprite->max = 4;
		sprite->state = 0;
	}
}
D3DXVECTOR2 Player::PlaneHead() {
	return position + D3DXVECTOR2(71, 35);
}
RECT Player::CalculateHitBox() {
	colWidth = 134;
	colHeight = 58;
	colXOffset = 4;
	colYOffset = 19;
	hitbox.left = position.x + colXOffset;
	hitbox.right = position.x + colWidth;
	hitbox.top = position.y + colYOffset;
	hitbox.bottom = position.y + colHeight;
	//hitbox.left = position.x;
	//hitbox.right = position.x + sprite->width;
	//hitbox.top = position.y;
	//hitbox.bottom = position.y + sprite->height;
	return hitbox;
}
