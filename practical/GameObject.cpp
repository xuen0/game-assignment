#include "GameObject.h"

GameObject::GameObject(Sprite* sprite, float mass, float power, int posX, int posY)
	:GameObject( sprite,  mass,  power,  posX,  posY, 0)
{}

GameObject::GameObject(Sprite* sprite, float mass, float power,int posX, int posY, float maxHp)
	:GameObject(sprite, mass, power, D3DXVECTOR2(posX, posY), maxHp){}
GameObject::GameObject(Sprite* sprite, float mass, float power, D3DXVECTOR2 position, float maxHp)
	:GameObject(sprite, mass, D3DXVECTOR2(power,power), position, maxHp) {}
GameObject::GameObject(Sprite* sprite, float mass, float verPower, float horPower, D3DXVECTOR2 position, float maxHp)
	:GameObject(sprite,mass, D3DXVECTOR2(horPower, verPower),position, maxHp) {}
GameObject::GameObject(Sprite* sprite, float mass, D3DXVECTOR2 power, D3DXVECTOR2 position)
	:GameObject( sprite,  mass,  power,  position,0){}
GameObject::GameObject(Sprite* sprite, float mass, D3DXVECTOR2 power, D3DXVECTOR2 position, float maxHp)
{
	this->sprite = sprite;
	this->position = position;
	startpos = position;
	transform = new Transform(this->sprite->width, this->sprite->height);
	physics = new Physics(mass, power);
	colWidth = sprite->width * 0.8;
	colHeight = sprite->height * 0.8;
	colXOffset = (sprite->width - colWidth) / 2;
	colYOffset = (sprite->height - colHeight) / 2;
	this->hp = maxHp;
	this->maxHp = maxHp;
	render = true;
}
GameObject::GameObject(GameObject* gameObject)
{
	sprite = new Sprite(gameObject->sprite);
	position = gameObject->position;
	startpos = gameObject->position;
	transform = new Transform(gameObject->sprite->width, gameObject->sprite->height);
	physics = new Physics(gameObject->physics->mass, gameObject->physics->power);
	colWidth = sprite->width * 0.8;
	colHeight = sprite->height * 0.8;
	colXOffset = (sprite->width - colWidth) / 2;
	colYOffset = (sprite->height - colHeight) / 2;
	hp = gameObject->maxHp;
	maxHp = gameObject->maxHp;
	render = true;
}
void GameObject::Render()
{
	if(render)sprite->Render(transform->Matrix(position));
}
void GameObject::Move() {
	physics->Move(&position);
	if (!(position.y > windowHeight - sprite->height)) {
		physics->force += gravity;
	}
}
bool GameObject::HitXBoundary() {
	return position.x < 0 || position.x > windowWidth - sprite->width * transform->scaling.x;
}
bool GameObject::HitTopBoundary() {
	return position.y < 0;
}
bool GameObject::HitBottomBoundary() {
	return position.y > windowHeight - sprite->height * transform->scaling.y;
}
bool GameObject::HitLeftBoundary() {
	return position.x < 0;
}
bool GameObject::HitRightBoundary() {
	return position.x > windowWidth - sprite->width * transform->scaling.x;
}
bool GameObject::HitYBoundary() {
	return position.y < 0 || position.y > windowHeight - sprite->height * transform->scaling.y;
}
bool GameObject::ExitBoundary() {
	return position.x + sprite->width < 0 || position.x > windowWidth * transform->scaling.x
		|| position.y + sprite->width < 0 || position.y > windowHeight * transform->scaling.y;
}

RECT GameObject::CalculateHitBox() {
	colWidth = sprite->width * transform->scaling.x;
	colHeight = sprite->height * transform->scaling.y;
	colXOffset = (sprite->width - colWidth) / 2;
	colYOffset = (sprite->height - colHeight) / 2;
	hitbox.left = position.x + colXOffset;
	hitbox.right = position.x + colWidth ;
	hitbox.top = position.y + colYOffset;
	hitbox.bottom = position.y + colHeight;
	return hitbox;
}
void GameObject::CleanUp()
{
	sprite->CleanUp();
}

void GameObject::CalculateAnimation()
{
	if (frame % 6 == 0) {
		sprite->NextFrame();
	}
}
void GameObject::TakeDamage(int dmg) {
	hp -= dmg;
	sprite->Red();
}
D3DXVECTOR2 GameObject::GetPosition() {
	return position;
}
void GameObject::SetPosition(D3DXVECTOR2 position) {
	this->position = position;
}
D3DXVECTOR2 GameObject::GetVelocity() {
	return physics->velocity;
}
void GameObject::SetVelocity(D3DXVECTOR2 velocity) {
	physics->velocity = velocity;
}

int GameObject::GetMass()
{
	return physics->mass;
}
void GameObject::SetMass(float mass) {
	physics->mass = mass;
}

void GameObject::ResetForce()
{
	physics->force *= 0;
}

float GameObject::GetHp()
{
	return hp;
}

float GameObject::GetMaxHp()
{
	return maxHp;
}

void GameObject::Scale(int x, int y)
{
	transform->Scale(x, y);
}

void GameObject::SetHp(float hp)
{
	this->hp = hp;
}

void GameObject::Reset()
{
	this->hp = maxHp;
	position = startpos;
	sprite->color = D3DCOLOR_XRGB(255, 255, 255);
}
