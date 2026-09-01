#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Shooter.h"
#include "Direction.h"
class Player :
    public GameObject, public Shooter
{
public:
    using GameObject :: GameObject;
    using Shooter::Shooter;
    Player(Sprite* sprite, float mass, float power, int posX, int posY, Bullet* bullet, int cooldown, float hp);
    void Move();
    void Render();
    void Shoot();
    void ChangeDirection(Direction direction);
    void CalculateAnimation();
    D3DXVECTOR2 PlaneHead();
    RECT CalculateHitBox() override;
};

