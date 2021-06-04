#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleBOSS.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	TurretDown.Empty();
	TurretDown.PushBack({173, 50, 19, 28});
	TurretDown.speed = 0.05f;
	TurretDownR.Empty();
	TurretDownR.PushBack({203, 50, 18, 28});
	TurretDownR.speed = 0.05f;
	TurretDownL.Empty();
	TurretDownL.PushBack({145, 50, 18, 28});
	TurretDownL.speed = 0.05f;
	TurretUp.Empty();
	TurretUp.PushBack({174, 80, 17, 22});
	TurretUp.speed = 0.05f;
	TurretUpR.Empty();
	TurretUpR.PushBack({202, 80, 20, 21});
	TurretUpR.speed = 0.05f;
	TurretUpL.Empty();
	TurretUpL.PushBack({143, 80, 20, 21});
	TurretUpL.speed = 0.05f;
	TurretLeft.Empty();
	TurretLeft.PushBack({135, 0, 24, 15});
	TurretLeft.speed = 0.05f;
	TurretLeftD1.Empty();
	TurretLeftD1.PushBack({168, 0, 24, 19});
	TurretLeftD1.speed = 0.05f;
	TurretLeftD2.Empty();
	TurretLeftD2.PushBack({203, 0, 21, 21});
	TurretLeftD2.speed = 0.05f;
	TurretLeftU1.Empty();
	TurretLeftU1.PushBack({168, 33, 24, 15});
	TurretLeftU1.speed = 0.05f;
	TurretLeftU2.Empty();
	TurretLeftU2.PushBack({201, 31, 22, 18});
	TurretLeftU2.speed = 0.05f;
	TurretRight.Empty();
	TurretRight.PushBack({199, 103, 24, 16});
	TurretRight.speed = 0.05f;
	TurretRightD1.Empty();
	TurretRightD1.PushBack({166, 103, 24, 20});
	TurretRightD1.speed = 0.05f;
	TurretRightD2.Empty();
	TurretRightD2.PushBack({133, 103, 22, 22});
	TurretRightD2.speed = 0.05f;
	TurretRightU1.Empty();
	TurretRightU1.PushBack({166, 137, 24, 15});
	TurretRightU1.speed = 0.05f;
	TurretRightU2.Empty();
	TurretRightU2.PushBack({135, 135, 22, 18});
	TurretRightU2.speed = 0.05f;

	collider = App->collisions->AddCollider({0, 0, 16, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	position.x = App->boss->x + 20;
	position.y = App->boss->y + 130;

	if (App->player->position.y > position.y){
		if (App->player->position.x < position.x - 46){
			TurretLeft.Reset();
  			currentAnim = &TurretLeft;
		}
		else if (App->player->position.x > position.x - 30 && App->player->position.x < position.x - 15){
			TurretLeftD1.Reset();
			currentAnim = &TurretLeftD2;
		}
		else if(App->player->position.x > position.x - 45 && App->player->position.x < position.x - 31){
			TurretLeftD2.Reset();
			currentAnim = &TurretLeftD1;
		}
		else if(App->player->position.x > position.x - 14 && App->player->position.x < position.x - 5){
			TurretDownL.Reset();
			currentAnim = &TurretDownL;
		}
		else if(App->player->position.x > position.x - 4 && App->player->position.x < position.x + 4){
			TurretDown.Reset();
			currentAnim = &TurretDown;
		}
		else if(App->player->position.x > position.x + 5 && App->player->position.x < position.x + 15){
			TurretDownR.Reset();
			currentAnim = &TurretDownR;
		}
		else if (App->player->position.x > position.x + 46) {
			TurretLeft.Reset();
			currentAnim = &TurretRight;
		}
		else if (App->player->position.x < position.x + 30 && App->player->position.x > position.x + 15) {
			TurretLeftD1.Reset();
			currentAnim = &TurretRightD2;
		}
		else if (App->player->position.x < position.x + 45 && App->player->position.x > position.x + 31) {
			TurretLeftD2.Reset();
			currentAnim = &TurretRightD1;
		}
	}
	else if(App->player->position.y < position.y){
		if (App->player->position.x < position.x - 46) {
			TurretLeft.Reset();
			currentAnim = &TurretLeft;
		}
		else if (App->player->position.x > position.x - 30 && App->player->position.x < position.x - 15) {
			TurretLeftD1.Reset();
			currentAnim = &TurretLeftU2;
		}
		else if (App->player->position.x > position.x - 45 && App->player->position.x < position.x - 31) {
			TurretLeftD2.Reset();
			currentAnim = &TurretLeftU1;
		}
		else if (App->player->position.x > position.x - 14 && App->player->position.x < position.x - 5) {
			TurretDownL.Reset();
			currentAnim = &TurretUpL;
		}
		else if (App->player->position.x > position.x - 4 && App->player->position.x < position.x + 4) {
			TurretDown.Reset();
			currentAnim = &TurretUp;
		}
		else if (App->player->position.x > position.x + 5 && App->player->position.x < position.x + 15) {
			TurretDownR.Reset();
			currentAnim = &TurretUpR;
		}
		else if (App->player->position.x > position.x + 46) {
			TurretLeft.Reset();
			currentAnim = &TurretRight;
		}
		else if (App->player->position.x < position.x + 30 && App->player->position.x > position.x + 15) {
			TurretLeftD1.Reset();
			currentAnim = &TurretRightU2;
		}
		else if (App->player->position.x < position.x + 45 && App->player->position.x > position.x + 31) {
			TurretLeftD2.Reset();
			currentAnim = &TurretRightU1;
		}
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
