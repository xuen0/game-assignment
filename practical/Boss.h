#pragma once
#include "Enemy.h"
#include "BabyEnemy.h"
class Boss :
    public Enemy
{
public:
    using Enemy::Enemy;
    int maxChildren;
    int babyCount;
    void Shoot();
    Boss(Sprite* sprite, float mass, float power, int posX, int posY, BabyEnemy* projectile, int cooldown, float maxHp);
    D3DXVECTOR2 Feet();
    RECT CalculateHitBox() override;
};

