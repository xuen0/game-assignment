#pragma once
#include"Bullet.h";
#include <list>
using namespace std;
class Shooter
{
public:
    int cooldown;
    int timeLeft;
    Bullet* bullet;
    list<Bullet*> gun;
    Shooter(Bullet* bullet, int cooldown);
    bool Shoot(D3DXVECTOR2 position);
    void MoveBullets();
    void Render();
    Shooter(Shooter* shooter);
};

