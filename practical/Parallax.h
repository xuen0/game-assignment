#pragma once
#include "Sprite.h"
class Parallax
{
public:
    Sprite* sprite[3];
    int current;
    D3DXVECTOR2 position;
    float speed;
    void Move();
    Parallax(Sprite* sprite, double speed);
    Parallax(Sprite* sprite, double speed, int posX, int posY);
    void Render();
    void CleanUp();
};

