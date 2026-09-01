#pragma once
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
class GameObject
{
protected:	
	Physics* physics;
	D3DXVECTOR2 position;
	D3DXVECTOR2 startpos;
	RECT hitbox;
	Sprite* sprite;
	Transform* transform;
	float hp;
	float maxHp;
	int colWidth;
	int colHeight;
	int colXOffset;
	int colYOffset;
	bool render;
public:
	D3DXVECTOR2 gravity = D3DXVECTOR2(0, 0);
	GameObject(Sprite* sprite, float mass, float power, int posX, int posY);
	GameObject(Sprite* sprite, float mass,float power, int posX, int posY,float maxHp);
	GameObject(Sprite* sprite, float mass, float power, D3DXVECTOR2 position, float maxHp);
	GameObject(Sprite* sprite, float mass, float horPower, float verPower, D3DXVECTOR2 position, float maxHp);
	GameObject(Sprite* sprite, float mass, D3DXVECTOR2 power, D3DXVECTOR2 position);
	GameObject(Sprite* sprite, float mass, D3DXVECTOR2 power, D3DXVECTOR2 position, float maxHp);
	GameObject(GameObject* gameObject);
	virtual void Render();
	virtual void Move();
	virtual bool HitXBoundary();
	virtual bool HitTopBoundary();
	virtual bool HitBottomBoundary();
	virtual bool HitLeftBoundary();
	virtual bool HitRightBoundary();
	virtual bool HitYBoundary();
	virtual bool ExitBoundary();
	virtual RECT CalculateHitBox();
	void CleanUp();
	virtual void CalculateAnimation();
	void TakeDamage(int dmg);
	D3DXVECTOR2 GetPosition();
	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetVelocity();
	void SetVelocity(D3DXVECTOR2 velocity);
	int GetMass();
	void SetMass(float mass);
	void ResetForce();
	float GetHp();
	float GetMaxHp();
	void Scale(int x, int y);
	void SetHp(float hp);
	void Reset();
};

