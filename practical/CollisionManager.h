#pragma once
#include "GameObject.h"
class CollisionManager
{
public:
	boolean CheckCollision(GameObject* gameObjectA, GameObject* gameObjectB);
	void knockback(GameObject* gameObjectA, GameObject* gameObjectB);
};

