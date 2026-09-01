#pragma once
#include "Bullet.h"
class Coconut :
    public Bullet
{
public:
    using Bullet::Bullet;
    Coconut(Coconut* Coconut);
    Bullet* Reload() override;
    void Out()override;
    void CalculateAnimation()override;
    bool ExitBoundary() override;
};

