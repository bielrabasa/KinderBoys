#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	DRAnim.PushBack({ 0, 112, 16, 16 });
	DLAnim.PushBack({ 96, 112, 16, 16 });
	DRAnim.PushBack({ 16, 128, 16, 16 });
	DownAnim.PushBack({ 48, 128, 16, 16 });
	DLAnim.PushBack({ 80, 128, 16, 16 });
	DRAnim.PushBack({ 32, 144, 16, 16 });
	DownAnim.PushBack({ 48, 144, 16, 16 });
	DLAnim.PushBack({ 64, 144, 16, 16 });
	RightAnim.PushBack({ 16, 160, 16, 16 });
	RightAnim.PushBack({ 32, 160, 16, 16 });
	LeftAnim.PushBack({ 64, 160, 16, 16 });
	LeftAnim.PushBack({ 80, 160, 16, 16 });
	URAnim.PushBack({ 32, 176, 16, 16 });
	UpAnim.PushBack({ 48, 176, 16, 16 });
	ULAnim.PushBack({ 64, 176, 16, 16 });
	URAnim.PushBack({ 16, 192, 16, 16 });
	UpAnim.PushBack({ 48, 192, 16, 16 });
	ULAnim.PushBack({ 80, 192, 16, 16 });
	URAnim.PushBack({ 0, 208, 16, 16 });
	ULAnim.PushBack({ 96, 208, 16, 16 });
	DownAnim.speed = 0.05f;
	UpAnim.speed = 0.05f;
	RightAnim.speed = 0.05f;
	LeftAnim.speed = 0.05f;
	URAnim.speed = 0.05f;
	ULAnim.speed = 0.05f;
	DLAnim.speed = 0.05f;
	DRAnim.speed = 0.05f;

	currentAnim = &DownAnim;
	
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
			position.y -= 1;
			currentAnim = &UpAnim;
			break;
		case 1:
			position.y += 1; //dalt
			currentAnim = &DownAnim;
			break;
		case 2:
			position.x += 1;
			currentAnim = &RightAnim;
			break;
		case 3:
			position.x -= 1;
			currentAnim = &LeftAnim;
			break;
		}
	}
	
	if (movementDelay >= 1 && spawntimer > 80) {
		if (position.x - App->player->position.x < 0)			//right
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &RightAnim) {
				RightAnim.Reset();
				currentAnim = &RightAnim;
			}
			position.x += 1.25;
		}
		else if (position.x - App->player->position.x > 0)		//left
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &LeftAnim) {
				LeftAnim.Reset();
				currentAnim = &LeftAnim;
			}
			position.x -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		if (position.y - App->player->position.y < 0)			//down
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &DownAnim) {
				DownAnim.Reset();
				currentAnim = &DownAnim;
			}
			position.y += 1.25;
		}
		else if (position.y - App->player->position.y > 0)		//up
		{
			movementDirections++;
			if (movementDirections < 2 && currentAnim != &UpAnim) {
				UpAnim.Reset();
				currentAnim = &UpAnim;
			}
			position.y -= 1.25;
		}
		else {
			movementDirections = 0;
		}

		//DIAGONALS
		if (movementDirections > 2) {
			if (position.y - App->player->position.y > 0) { //up

				if (position.x - App->player->position.x > 0 && currentAnim != &ULAnim) { //left
					ULAnim.Reset();
					currentAnim = &ULAnim;
				}
				else if (position.x - App->player->position.x < 0 && currentAnim != &URAnim) { //right
					URAnim.Reset();
					currentAnim = &URAnim;
				}
			}
			else { //down
				if (position.x - App->player->position.x > 0 && currentAnim != &DLAnim) { //left
					DLAnim.Reset();
					currentAnim = &DLAnim;
				}
				else if (position.x - App->player->position.x < 0 && currentAnim != &DRAnim) { //right
					DRAnim.Reset();
					currentAnim = &DRAnim;
				}
			}
		}

		movementDelay = 0;
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
