#pragma once
#include "GameObject.h"
#include "Shooter.h"
class Enemy :
    virtual public GameObject, virtual public Shooter
{
public:
    int maxVerticalMove;
    int movement;
    Direction current;
    void Move() override;
    void Shoot();
    Enemy(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* projectile, int cooldown, float maxHp);
    Enemy(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY, Bullet* projectile, int cooldown, float maxHp);
    D3DXVECTOR2 Ground();
    D3DXVECTOR2 Feet();
    void Reset();
    void Render();
    void CalculateAnimation() override;
    RECT CalculateHitBox();
    Enemy(Enemy* enemy);
};

