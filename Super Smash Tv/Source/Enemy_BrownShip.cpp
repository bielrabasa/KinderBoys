#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0, 112, 16, 16 });
	fly.PushBack({ 96, 112, 16, 16 });
	fly.PushBack({ 16, 128, 16, 16 });
	fly.PushBack({ 48, 128, 16, 16 });
	fly.PushBack({ 80, 128, 16, 16 });
	fly.PushBack({ 32, 144, 16, 16 });
	fly.PushBack({ 48, 144, 16, 16 });
	fly.PushBack({ 64, 144, 16, 16 });
	fly.PushBack({ 16, 160, 16, 16 });
	fly.PushBack({ 32, 160, 16, 16 });
	fly.PushBack({ 64, 160, 16, 16 });
	fly.PushBack({ 80, 160, 16, 16 });
	fly.PushBack({ 32, 176, 16, 16 });
	fly.PushBack({ 48, 176, 16, 16 });
	fly.PushBack({ 64, 176, 16, 16 });
	fly.PushBack({ 16, 192, 16, 16 });
	fly.PushBack({ 48, 192, 16, 16 });
	fly.PushBack({ 80, 192, 16, 16 });
	fly.PushBack({ 0, 208, 16, 16 });
	fly.speed = 0.1f;
	currentAnim = &fly;
	
	//path.PushBack({-1.0f, -0.5f}, 100);
	//path.PushBack({-1.0f, 0.5f}, 80);
	//path.PushBack({-1.0f, 1.0f}, 80);
	
	collider = App->collisions->AddCollider({0, 0, 16, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	//path.Update();
	//position = spawnPos + path.GetRelativePosition();
	movementDelay++;
	spawntimer++;

	if (spawntimer <= 80) {
		switch (App->sceneLevel_1->i) {
		case 0:
			position.y -= 1.25;
			break;
		case 1:
			position.y += 1.25; //dalt
			break;
		case 2:
			position.x += 1.25;
			break;
		case 3:
			position.x -= 1.25;
			break;
		}
	}
	
	if (movementDelay >= 1 && spawntimer > 80) {
		if (position.x - App->player->position.x < 0)
		{
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)
		{
			position.x -= 1.25;
		}

		if (position.y - App->player->position.y < 0)
		{
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)
		{
			position.y -= 1.25;
		}

		movementDelay = 0;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
