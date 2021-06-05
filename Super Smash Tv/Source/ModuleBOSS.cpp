#include "ModuleBOSS.h"
using namespace std;

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Particle.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "Enemy_Turret2.h"
#include "Enemy_Mech.h"

ModuleBOSS::ModuleBOSS(bool startEnabled) : Module(startEnabled)
{
	IdleHead.Empty();
	IdleHead.PushBack({ 32, 0, 32, 32 }); //3 iguals perquè duri més amb la boca tancada que oberta
	IdleHead.PushBack({ 32, 0, 32, 32 });
	IdleHead.PushBack({ 32, 0, 32, 32 });
	IdleHead.PushBack({ 33, 32, 32, 32 });
	IdleHead.loop = true;
	IdleHead.speed = 0.01f;

	RHead.Empty();
	RHead.PushBack({ 65, 0, 30, 32 });
	RHead.PushBack({ 65, 0, 30, 32 });
	RHead.PushBack({ 65, 0, 30, 32 });
	RHead.PushBack({ 64, 32, 32, 32 });
	RHead.loop = true;
	RHead.speed = 0.01f;

	LHead.Empty();
	LHead.PushBack({ -2, 0, 32, 32 });
	LHead.PushBack({ -2, 0, 32, 32 });
	LHead.PushBack({ -2, 0, 32, 32 });
	LHead.PushBack({ 0, 32, 32, 32 });
	LHead.loop = true;
	LHead.speed = 0.01f;

	Body.Empty();
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1
	Body.PushBack({ 256, 73, 128, 80 });	//1

	Body.PushBack({ 384, 73, 128, 80 });	//2
	Body.PushBack({ 0, 73, 128, 80 });		//3
	Body.PushBack({ 128, 73, 128, 80 });	//4
	Body.PushBack({ 128, 73, 128, 80 });	//4
	Body.PushBack({ 0, 73, 128, 80 });		//3
	Body.PushBack({ 384, 73, 128, 80 });	//2
	Body.loop = true;
	Body.speed = 0.03f;

	Body2.Empty();
	Body2.PushBack({ 256, 0, 128, 64 });
	Body2.loop = true;
	Body2.speed = 0.5;

	Body3.Empty();
	Body3.PushBack({ 128, 0, 128, 64 });
	Body3.loop = true;
	Body3.speed = 0.5;

	RightArm.Empty();
	RightArm.PushBack({ 96, 0, 32, 32 });
	RightArm.loop = true;
	RightArm.speed = 0.5;

	emptyAnimation.Empty();
	emptyAnimation.PushBack({ 0, 0, 1, 1 });
	emptyAnimation.loop = true;
	emptyAnimation.speed = 0.5;

	Wheels.Empty();
	Wheels.PushBack({ 0, 192, 64, 96 });
	Wheels.PushBack({ 64, 192, 64, 96 });
	Wheels.PushBack({ 128, 192, 64, 96 });
	Wheels.loop = true;
	Wheels.speed = 0.07f;

	HeadAnimation = &IdleHead;
	BodyAnimation = &Body;
	WheelsAnimation = &Wheels;
	ArmAnimation = &emptyAnimation;

	TurretDown.Empty();
	TurretDown.PushBack({ 173, 50, 19, 28 });
	
	LTurret = &TurretDown;
	RTurret = &TurretDown;
}

ModuleBOSS::~ModuleBOSS()
{
	
}

// Load assets
bool ModuleBOSS::Start()
{
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	LOG("Loading background assets");
	
	bool ret = true;

	x = 192; //Wheels centered (horizontal), 192 està perfecte
	y = -150; //Wheels out of the map (top), 150 està perfecte

	bgTexture = App->textures->Load("Assets/SpritesSSTV/sprite_boss.png");
	enemyTexture = App->textures->Load("Assets/SpritesSSTV/Entity_Green_and_Pink.png");

	bossTimer = 0;

	currentvidaBOSS = 150;

	collider = App->collisions->AddCollider({ x + xoffset, y + yoffset, 108, 120 } , Collider::Type::BOSS, this);

	App->enemies->AddEnemy(Enemy_Type::MECH, 0, 0);
	App->enemies->AddEnemy(Enemy_Type::TURRET2, 0, 0);

	App->player->ImprimirPortes = false;

	return ret;
}

bool ModuleBOSS::CleanUp() {
	App->textures->Unload(bgTexture);
	App->player->ImprimirPortes = true;
	return true;
}

UpdateResult ModuleBOSS::Update()
{

	if (currentvidaBOSS == 0) {
		HeadAnimation = &emptyAnimation;
		BodyAnimation = &emptyAnimation;
		WheelsAnimation = &emptyAnimation;
		ArmAnimation = &emptyAnimation;
		App->fade->FadeToBlack((Module*)App->sceneLevel2, (Module*)App->sceneWin, 20);
	}

	if (startlvl >= 350) {
			if (y == 65) {
				y++;
			}
			if (y == 296) {
				y--;
			}
			if (x == 18) {
				x++;
			}
			if (x >= 360) {
				x--;
			}
	}

	//Treballar amb 'x' i 'y' del Boss
	startlvl++;
	if (startlvl >=350) {
		if (contmovx == 0) {
			movimiento_x = rand() % 4;
			contmovx++;
		}

		//movimiento_y = rand() % 2;
		contmovx++;
		if (contmovx != 0) {
			if (contmovx >= 50) {
				contmovx = 0;
			}
			if (movimiento_x == 0) { x--; }
			else if (movimiento_x == 1) { x++; }
			else if (movimiento_x == 2) { y--; }
			else if (movimiento_x == 3) { y++; }
		}
		
	}

	
	if (App->input->keys[SDL_SCANCODE_M] == KeyState::KEY_DOWN&&bandera==true) {
		bandera = false;
	}
	else if (App->input->keys[SDL_SCANCODE_M] == KeyState::KEY_DOWN&&bandera==false) {
		bandera = true;
	}
	if (bandera==false) {
		
		contShot+=5;
		if (contShot >= 200) {
			if (Shots >= 60) {
				contShot = 0;
				Shots = 0;
				explosiontimer = 0;
			}
			cont++;
			if (cont >= 10) { //DELAY
				Shots+=10;
				baderaShot = true;
				cont = 0;
				TimeShot = true;
			}
			
			else if(cont<=9) {
				baderaShot = false;
			}
		}
		}
		if (baderaShot) {
			if(App->player->position.x < x+40){//Posicio mes esquerra adalt
				if (App->player->position.y < y +20) {
					App->particles->laserBossL.speed.x = -3;
					App->particles->laserBossL.speed.y =-1;
					App->particles->AddParticle(App->particles->laserBossL, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x - 90, y , 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x > x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y < y + 20) {
					App->particles->laserBossR.speed.x = 3;
					App->particles->laserBossR.speed.y = -1;
					App->particles->AddParticle(App->particles->laserBossR, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x + 154, y, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x < x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 21 && App->player->position.y<y+100) {
					App->particles->laserBossLD1.speed.x = -3;
					App->particles->laserBossLD1.speed.y = -2;
					App->particles->AddParticle(App->particles->laserBossLD1, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x - 84, y+37, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x < x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 101 && App->player->position.y < y + 180) {
					App->particles->laserBossLD2.speed.x = -3;
					App->particles->laserBossLD2.speed.y = -4;
					App->particles->AddParticle(App->particles->laserBossLD2, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x - 81, y + 117, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x < x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 180 && App->player->position.y < y + 500) {
					App->particles->laserBossLD3.speed.x = -3;
					App->particles->laserBossLD3.speed.y = -6;
					App->particles->AddParticle(App->particles->laserBossLD3, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x - 78, y + 197, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x > x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 21 && App->player->position.y < y + 100) {
					App->particles->laserBossRD1.speed.x = 3;
					App->particles->laserBossRD1.speed.y = -2;
					App->particles->AddParticle(App->particles->laserBossRD1, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x + 148, y + 37, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;

					}
				}
			}
			if (App->player->position.x > x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 101 && App->player->position.y < y + 180) {
					App->particles->laserBossRD2.speed.x = 3;
					App->particles->laserBossRD2.speed.y = -4;
					App->particles->AddParticle(App->particles->laserBossRD2, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x + 148, y + 117, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;
					}
				}
			}
			if (App->player->position.x > x + 40) {//Posicio mes esquerra adalt
				if (App->player->position.y > y + 180 && App->player->position.y < y + 500) {
					App->particles->laserBossRD3.speed.x = 3;
					App->particles->laserBossRD3.speed.y = -6;
					App->particles->AddParticle(App->particles->laserBossRD3, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x + 145, y + 197, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;
					}
				}
			}
			if (App->player->position.x < x - 20&& App->player->position.x > x + 20) {//Down
				if (App->player->position.y > y + 180 && App->player->position.y < y + 500) {
					App->particles->laserBossD.speed.x = 0;//Arreglar velocidades para vertical shot
					App->particles->laserBossD.speed.y = -1;
					App->particles->AddParticle(App->particles->laserBossD, x + 35, y - 40, 6, Collider::Type::ENEMY_SHOT);
					App->audio->PlayFx(laserFx);
					if (explosiontimer >= 39) {
						App->particles->AddParticle(App->particles->laserBossLEx, x + 20, y + 200, 0, Collider::Type::ExplosionEnemicShot);
						TimeShot = false;
						explosiontimer = 0;
					}
				}
			}
		}
		if (TimeShot) {
			explosiontimer++;
		}
		if (!TimeShot) {
			explosiontimer = 0;
		}
		
		
		
	

	//Animacions
	if (App->player->position.x < x - 50) {
		HeadAnimation = &LHead;
	}
	else if (App->player->position.x > x + 150) {
		HeadAnimation = &RHead;
	}
	else {
		HeadAnimation = &IdleHead;
	}
	if (currentvidaBOSS != 0) {
		switch (currentvidaBOSS / 30) {
		case 5:
		case 4:
			ArmAnimation = &emptyAnimation;
			BodyAnimation = &Body;
			break;
		case 3:
			ArmAnimation = &RightArm;
			BodyAnimation = &Body3;
			break;
		case 2:
			ArmAnimation = &emptyAnimation;
			BodyAnimation = &Body3;
			break;
		case 1:
			ArmAnimation = &emptyAnimation;
			BodyAnimation = &Body2;
			break;
		case 0:
			offsetYhead = -10;
			ArmAnimation = &emptyAnimation;
			BodyAnimation = &emptyAnimation;
		default:
			break;
		}
	}

	collider->SetPos(x + xoffset, y + yoffset);

	WheelsAnimation->Update();
	BodyAnimation->Update();
	HeadAnimation->Update();
	ArmAnimation->Update();

	
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleBOSS::PostUpdate()
{
	SDL_Rect RectWheels = WheelsAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x, y, &RectWheels, 2); //no sumem ni restem
	
	SDL_Rect RectBody = BodyAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x - 70, y - 70, &RectBody, 2); //x-70 y-70 centrat
	
	SDL_Rect RectHead = HeadAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x + 32, y + offsetYhead, &RectHead, 2); //x+32 y-64 centrat

	SDL_Rect RectArm = ArmAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x + 106, y - 38, &RectArm, 2); // 106 -38

	if (LTurret != nullptr)
		App->render->DrawTexture(enemyTexture, torreta1x, torreta1y, &(LTurret->GetCurrentFrame()), 1.5f);

	if (RTurret != nullptr)
		App->render->DrawTexture(enemyTexture, torreta2x, torreta2y, &(RTurret->GetCurrentFrame()), 1.5f);

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleBOSS::OnCollision(Collider* c1, Collider* c2) {
	
	
	if (c2->type == c2->PLAYER_TRIPLE_SHOT)
	{
		if (currentvidaBOSS > 0)
			currentvidaBOSS--;
	}
}