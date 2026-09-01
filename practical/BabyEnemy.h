#pragma once
#include "Bullet.h"
#include "Shooter.h"
class BabyEnemy :
    public Bullet, public Shooter
{
public:
    using Bullet::Bullet, Shooter::Shooter;
    int maxVerticalMove;
    int movement;
    int maxHorizontalMove;
    Direction current;
    void Move() override;
    void Shoot();
    BabyEnemy(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY, Bullet* projectile, int cooldown, float maxHp);
    BabyEnemy(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* projectile, int cooldown, float maxHp);
    D3DXVECTOR2 Feet();
    void Render();
    BabyEnemy(BabyEnemy* enemy);
    Bullet* Reload() override;
    void Out()override;
    RECT CalculateHitbox();
    void CalculateAnimation();
};


