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

	Wheels.Empty();
	Wheels.PushBack({ 0, 192, 64, 96 });
	Wheels.PushBack({ 64, 192, 64, 96 });
	Wheels.PushBack({ 128, 192, 64, 96 });
	Wheels.loop = true;
	Wheels.speed = 0.07f;

	HeadAnimation = &IdleHead;
	BodyAnimation = &Body;
	WheelsAnimation = &Wheels;

	//Pit Trencat	{ 128, 0, 64, 64 }
	//Pit Trencat2	{ 196, 0, 64, 64 }

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

	bossTimer = 0;

	collider = App->collisions->AddCollider({ x + xoffset, y + yoffset, 108, 120 } , Collider::Type::BOSS, this);

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
	//Treballar amb 'x' i 'y' del Boss

	
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
			if (TimeShot) {
				TimeShotInt++;
				if (TimeShotInt >= 46) {
					TimeShotInt = 0;
					App->particles->AddParticle(App->particles->laserBossLEx, x - 150, y, 0, Collider::Type::ExplosionEnemicShot);
					TimeShot = false;
					
				}
			}
		}
		}
		if (baderaShot) {
			App->particles->AddParticle(App->particles->laserBossL, x, y, 2, Collider::Type::ENEMY_SHOT);
			App->audio->PlayFx(laserFx);
			//App->particles->AddParticle(App->particles->laserBossLEx, x - 150, y, 0, Collider::Type::ExplosionEnemicShot);
		}
		/*if (TimeShot) {
			explosiontimer++;
		}
		if (explosiontimer >= 29) {
			App->particles->AddParticle(App->particles->laserBossLEx, x - 150, y, 0, Collider::Type::ExplosionEnemicShot);
			TimeShot = false;
		}*/
	
		
	

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

	collider->SetPos(x + xoffset, y + yoffset);

	WheelsAnimation->Update();
	BodyAnimation->Update();
	HeadAnimation->Update();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleBOSS::PostUpdate()
{
	SDL_Rect RectWheels = WheelsAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x, y, &RectWheels, 2); //no sumem ni restem
	
	SDL_Rect RectBody = BodyAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x - 70, y - 70, &RectBody, 2); //x-70 y-70 centrat
	
	SDL_Rect RectHead = HeadAnimation->GetCurrentFrame();
	App->render->DrawTexture(bgTexture, x + 32, y - 64, &RectHead, 2); //x+32 y-64 centrat

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleBOSS::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == c2->PLAYER_TRIPLE_SHOT)
	{
		if (vidaBOSS > 0)
			vidaBOSS--;

	}
}