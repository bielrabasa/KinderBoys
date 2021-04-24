#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 0, 0, 16, 16 });
	flyAnim.PushBack({ 96, 0, 16, 16 });
	flyAnim.PushBack({ 16, 16, 16, 16 });
	flyAnim.PushBack({ 48, 16, 16, 16 });
	flyAnim.PushBack({ 80, 16, 16, 16 });
	flyAnim.PushBack({ 32, 32, 16, 16 });
	flyAnim.PushBack({ 48, 32, 16, 16 });
	flyAnim.PushBack({ 64, 32, 16, 16 });
	flyAnim.PushBack({ 0, 96, 16, 16 });
	flyAnim.speed = 0.1f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 16, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{
	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 0;

	/*if ((c1 == collider) && (destroyed == false)
	{
		position.x -= 1;
	}
	else
	{
		position.x -= 1;
	}*/
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
