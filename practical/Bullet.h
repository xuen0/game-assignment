#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
public:
    using GameObject::GameObject;
    Bullet(Bullet* bullet);
    virtual Bullet* Reload();
    virtual void Out();
    Bullet(Sprite* sprite, float mass, float horPower, float verPower, int posX, int posY);
};

