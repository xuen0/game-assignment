#include "Parallax.h"

void Parallax::Move()
{
	position.x -= 5* speed;
	if (position.x < -sprite[current]->width) {
		current = (current + 1) % 3;
		position.x = 0;
	}
}
Parallax::Parallax(Sprite* sprite, double speed) :Parallax(sprite, speed, 0, 0) {}
Parallax::Parallax(Sprite* sprite,double speed, int posX, int posY) {
	position = D3DXVECTOR2(posX, posY);
	for (int i = 0; i < 3; i++) {
		this->sprite[i] = new Sprite(&sprite->texture,sprite);//copy sprite
	}
	current = 0;
	this->speed = speed;
}
void Parallax::Render() {
	for (int i = 0; i < 3; i++) {
		D3DXVECTOR2 position = D3DXVECTOR2(this->position.x + i * sprite[i]->width, this->position.y);
		sprite[(current+i)%3]->Render(position);
	}
}
void Parallax::CleanUp() {
	sprite[0]->texture->Release();
	sprite[0]->texture = NULL;
}
