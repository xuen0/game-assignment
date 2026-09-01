#include "CollisionManager.h"

boolean CollisionManager::CheckCollision(GameObject* gameObjectA, GameObject* gameObjectB)
{
	RECT hitBoxA = gameObjectA->CalculateHitBox();
	RECT hitBoxB = gameObjectB->CalculateHitBox();
	if ((hitBoxA.top > hitBoxB.bottom) ||
		(hitBoxA.bottom < hitBoxB.top) ||
		(hitBoxA.right < hitBoxB.left) ||
		(hitBoxA.left > hitBoxB.right)) {
		return false;
	}
	return true;
}

void CollisionManager::knockback(GameObject* gameObjectA, GameObject* gameObjectB)
{
	//formulas:
			// * convert all vectors to unit vectors
			// v1	= v1n + u1t 
			// v2	= v2n + u2t 
			// v1n	= (u1n * (m1 - m2) + 2 * (m2 + u2n)) / (m1+m2)
			// v2n	= (u2n * (m1 - m2) + 2 * (m2 + u1n)) / (m1+m2)	
			// u1n	= n • u1
			// u2n	= n • u2
			// n	= unit vector of (p2 - p1)
			// meanings:
			// v1	: velocity of object 1 after collision
			// v2	: velocity of object 2 after collision
			// v1n	: normal velocity of object 1 after collision
			// v2n	: normal velocity of object 2 after collision
			// u1t	: perpendicular velocity of object 1
			// u2t	: perpendicular velocity of object 2 
			// m1	: object 1 mass
			// m2	: object 2 mass
			// u1n	: normal velocity of object 1 before collision
			// u2n	: normal velocity of object 2 before collision
			// u1	: velocity of object 1 before collision
			// u2	: velocity of object 2 before collision
			// n	: normal (line of collision)
			// t	: line perpendicular to normal
			// p1	: position of object 1
			// p2	: position of object 2

			// 1. find n and t
	D3DXVECTOR2 distance = gameObjectA->GetPosition() - gameObjectB->GetPosition();	/* p1 - p2  */
	D3DXVECTOR2 n;													/* unit vector of normal */
	D3DXVec2Normalize(&n, &distance);								/* (x2-x1 , y2-y1) / sqrt((x2-x1)^2+(y2-y1)^2))*/
	D3DXVECTOR2 t = D3DXVECTOR2(-n.y, n.x);							// t = perpendicular to normal

	// 2. convert inital velocities to unit vectors
	D3DXVECTOR2 u1 = gameObjectA->GetVelocity();// velocity of object 1 before collision
	D3DXVECTOR2 u2 = gameObjectB->GetVelocity();// velocity of object 2 before collision

	// 3. find u1n, u2n, u1t, u2t
	float u1n = D3DXVec2Dot(&n, &u1);								// u1n	= n • u1
	float u2n = D3DXVec2Dot(&n, &u2);								// u2n	= n • u2
	float u1t = D3DXVec2Dot(&t, &u1);								// u1t	= t • u1
	float u2t = D3DXVec2Dot(&t, &u2);								// u2t	= t • u2

	// 4. find v1n and v2n
	int m1 = gameObjectA->GetMass();
	int m2 = gameObjectB->GetMass();
	float v1n = (u1n * (m1 - m2) + 2 * m2 * u2n) / (m1 + m2);		// normal velocity of object 1 after collision
	float v2n = (u2n * (m1 - m2) + 2 * m1 * u1n) / (m1 + m2);		// normal velocity of object 1 after collision

	// 5.final velocities
	D3DXVECTOR2 v1 = (v1n * n + u1t * t);
	D3DXVECTOR2 v2 = (v2n * n + u2t * t);
	gameObjectA->SetVelocity(v1);							// convert v1n to vector by multiplyig n, same for u1t
	gameObjectB->SetVelocity(v2);							// convert v2n to vector by multiplyig n, same for u2t
	gameObjectA->ResetForce();
	gameObjectB->ResetForce();
	gameObjectA->Move();
	gameObjectB->Move();
}
