#include "Coconut.h"
Coconut::Coconut(Coconut* coconut):Bullet(coconut)
{
	gravity = D3DXVECTOR2(0, 0.1);
}
Bullet* Coconut::Reload()
{
	return new Coconut(this);
}
void Coconut::Out() {
	physics->force.x = sin(DegToRad(-30)) * physics->power.x;
	physics->force.y = -cos(DegToRad(-30)) * physics->power.y;
}
void Coconut::CalculateAnimation()
{
	transform->Rotate(-0.15);
}
bool Coconut::ExitBoundary() {
	return position.x + sprite->width < 0 || position.x > windowWidth || position.y > windowHeight;
}