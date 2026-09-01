#include "Shooter.h"
#include "Coconut.h"
#include <iostream>
using namespace std;
Shooter::Shooter(Bullet* bullet, int cooldown) {
	this->bullet = bullet;
	this->cooldown = cooldown;
	timeLeft = 0;
}
bool Shooter::Shoot(D3DXVECTOR2 position)
{
	if (timeLeft <= 0) {
		timeLeft = cooldown;
		bullet->SetPosition(position);
		Bullet* bullet = this->bullet->Reload();
		bullet->Out();
		audioManager->PlayGunShot();
		gun.push_front(bullet);
		return true;
	}
	return false;
}
void Shooter::MoveBullets() {
	timeLeft--;
	list<Bullet*>::iterator it;
	list<Bullet*> toRemove;
	for (it = gun.begin(); it != gun.end(); ++it) {
		Bullet* bullet = *it;
		bullet->Move();
		if(bullet->ExitBoundary()){
			toRemove.push_back(bullet);
		}
	}
	for (it = toRemove.begin(); it != toRemove.end(); ++it) {
		Bullet* bullet = *it;
		gun.remove(bullet);
	}
	toRemove.clear();
}

void Shooter::Render()
{
	list<Bullet*>::iterator it;
	for (it = gun.begin(); it != gun.end(); ++it) {
		(*it)->CalculateAnimation();
		(*it)->Render();
	}
}

Shooter::Shooter(Shooter* shooter)
{
	gun.clear();
	bullet = shooter->bullet->Reload();
	cooldown = shooter->cooldown;
	timeLeft = 0;
}