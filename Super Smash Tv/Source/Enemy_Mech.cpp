#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SceneLevel1.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleBOSS.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	App->enemies->videsTorreta = 7;

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
	if(currentAnim == &TurretLeft){
	position.x = App->boss->x + 5;
	position.y = App->boss->y + 93;
	}
	else if(currentAnim == &TurretLeftD2){
	position.x = App->boss->x + 9;
	position.y = App->boss->y + 93;
	}
	else if(currentAnim == &TurretLeftD1){
	position.x = App->boss->x + 10;
	position.y = App->boss->y + 93;
	}
	else if(currentAnim == &TurretDownL){
	position.x = App->boss->x + 14;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretDown){
	position.x = App->boss->x + 13;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretDownR){
	position.x = App->boss->x + 13;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretRight){
	position.x = App->boss->x + 12;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretRightD2){
	position.x = App->boss->x + 14;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretRightD1){
	position.x = App->boss->x + 9;
	position.y = App->boss->y + 93;
	}


	else if(currentAnim == &TurretLeft){
	position.x = App->boss->x + 5;
	position.y = App->boss->y + 93;
	}
	else if(currentAnim == &TurretLeftU2){
	position.x = App->boss->x + 10;
	position.y = App->boss->y + 93;
	}
	else if(currentAnim == &TurretLeftU1){
	position.x = App->boss->x + 10;
	position.y = App->boss->y + 89;
	}
	else if(currentAnim == &TurretUpL){
	position.x = App->boss->x + 12;
	position.y = App->boss->y + 83;
	}
	else if(currentAnim == &TurretUp){
	position.x = App->boss->x + 16;
	position.y = App->boss->y + 82;
	}
	else if(currentAnim == &TurretUpR){
	position.x = App->boss->x + 12;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretRight){
	position.x = App->boss->x + 12;
	position.y = App->boss->y + 90;
	}
	else if(currentAnim == &TurretRightU2){
	position.x = App->boss->x + 15;
	position.y = App->boss->y + 86;
	}	
	else if(currentAnim == &TurretRightU1){
	position.x = App->boss->x + 18;
	position.y = App->boss->y + 89;
	}



	/*if (App->player->position.y < position.y - 15 && App->player->position.y < position.y - 15)
	{
		if (App->player->position.x > position.x - 30 && App->player->position.x < position.x - 15) {
			TurretLeftD1.Reset();
			currentAnim = &TurretLeftD2;
		}
		else if (App->player->position.x > position.x - 45 && App->player->position.x < position.x - 31) {
			TurretLeftD2.Reset();
			currentAnim = &TurretLeftD1;
		}
	}*/


	//Move de la torreta seguint al player
	if (App->player->position.y > position.y){
		if (App->player->position.x < position.x - 46){
			TurretLeft.Reset();
  			currentAnim = &TurretLeft;
		}
		else if ((App->player->position.x > position.x - 30 && App->player->position.x < position.x - 15 ) || (App->player->position.y > position.y - 20 && App->player->position.y < position.y - 50)){
			TurretLeftD2.Reset();
			currentAnim = &TurretLeftD2;
		}
		else if(App->player->position.x > position.x - 45 && App->player->position.x < position.x - 31){
			TurretLeftD1.Reset();
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
			TurretRight.Reset();
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
			TurretLeftU2.Reset();
			currentAnim = &TurretLeftU2;
		}
		else if (App->player->position.x > position.x - 45 && App->player->position.x < position.x - 31) {
			TurretLeftU1.Reset();
			currentAnim = &TurretLeftU1;
		}
		else if (App->player->position.x > position.x - 14 && App->player->position.x < position.x - 5) {
			TurretUpL.Reset();
			currentAnim = &TurretUpL;
		}
		else if (App->player->position.x > position.x - 4 && App->player->position.x < position.x + 4) {
			TurretUp.Reset();
			currentAnim = &TurretUp;
		}
		else if (App->player->position.x > position.x + 5 && App->player->position.x < position.x + 15) {
			TurretUpR.Reset();
			currentAnim = &TurretUpR;
		}
		else if (App->player->position.x > position.x + 46) {
			TurretRight.Reset();
			currentAnim = &TurretRight;
		}
		else if (App->player->position.x < position.x + 30 && App->player->position.x > position.x + 15) {
			TurretRightU2.Reset();
			currentAnim = &TurretRightU2;
		}
		else if (App->player->position.x < position.x + 45 && App->player->position.x > position.x + 31) {
			TurretRightU1.Reset();
			currentAnim = &TurretRightU1;
		}
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
