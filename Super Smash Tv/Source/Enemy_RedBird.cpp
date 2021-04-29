#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "SceneLevel1.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	DLAnim.PushBack({ 0, 0, 16, 16 });
	DRAnim.PushBack({ 96, 0, 16, 16 });
	DLAnim.PushBack({ 16, 16, 16, 16 });
	DownAnim.PushBack({ 48, 16, 16, 16 });
	DRAnim.PushBack({ 80, 16, 16, 16 });
	DLAnim.PushBack({ 32, 32, 16, 16 });
	DownAnim.PushBack({ 48, 32, 16, 16 });
	DRAnim.PushBack({ 64, 32, 16, 16 });
	LeftAnim.PushBack({ 16, 48, 16, 16 });
	LeftAnim.PushBack({ 32, 48, 16, 16 });
	RightAnim.PushBack({ 64, 48, 16, 16 });
	RightAnim.PushBack({ 80, 48, 16, 16 });
	ULAnim.PushBack({ 32, 64, 16, 16 });
	UpAnim.PushBack({ 48, 64, 16, 16 });
	URAnim.PushBack({ 64, 64, 16, 16 });
	ULAnim.PushBack({ 16, 80, 16, 16 });
	UpAnim.PushBack({ 48, 80, 16, 16 });
	URAnim.PushBack({ 80, 80, 16, 16 });
	ULAnim.PushBack({ 0, 96, 16, 16 });
	URAnim.PushBack({ 96, 96, 16, 16 });
	DownAnim.speed = 0.05f;
	UpAnim.speed = 0.05f;
	RightAnim.speed = 0.05f;
	LeftAnim.speed = 0.05f;
	URAnim.speed = 0.05f;
	ULAnim.speed = 0.05f;
	DLAnim.speed = 0.05f;
	DRAnim.speed = 0.05f;

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
			currentAnim = &UpAnim;
			break;
		case 1:
			position.y += 1; 
			currentAnim = &DownAnim;
			break; 
		case 2:
			position.x += 1;
			currentAnim = &LeftAnim;
			break;
		case 3:
			position.x -= 1;
			currentAnim = &RightAnim;
			break;
		}
	}
	
	if (movementDelay >= 2 && spawntimer > 80) {
		if (position.x - App->player->position.x < 0)
		{
			currentAnim = &LeftAnim;
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)
		{
			currentAnim = &RightAnim;
			position.x -= 1.25;
		}

		if (position.y - App->player->position.y < 0)
		{
			currentAnim = &DownAnim;
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)
		{
			currentAnim = &UpAnim;
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

