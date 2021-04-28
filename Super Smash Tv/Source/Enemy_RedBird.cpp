#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel1.h"

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
	flyAnim.PushBack({ 16, 48, 16, 16 });
	flyAnim.PushBack({ 32, 48, 16, 16 });
	flyAnim.PushBack({ 64, 48, 16, 16 });
	flyAnim.PushBack({ 80, 48, 16, 16 });
	flyAnim.PushBack({ 32, 64, 16, 16 });
	flyAnim.PushBack({ 48, 64, 16, 16 });
	flyAnim.PushBack({ 64, 64, 16, 16 });
	flyAnim.PushBack({ 16, 80, 16, 16 });
	flyAnim.PushBack({ 48, 80, 16, 16 });
	flyAnim.PushBack({ 80, 80, 16, 16 });
	flyAnim.PushBack({ 0, 96, 16, 16 });
	flyAnim.PushBack({ 96, 96, 16, 16 });
	flyAnim.speed = 0.1f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 16, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{
	movementDelay++;
	spawntimer++;
	
	if (spawntimer <= 80) {
		switch (App->sceneLevel_1->i) {
		case 0:
			position.y -= 1;
			break;
		case 1:
			position.y += 1; //dalt
			break; 
		case 2:
			position.x += 1;
			break;
		case 3:
			position.x -= 1;
			break;
		}
	}
	
	if (movementDelay >= 2 && spawntimer > 80) {
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

	/*waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));

	if ((c1 == collider) && (destroyed == false)
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

/*void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == c2->WALL) {
		
	}

}*/

