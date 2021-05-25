#include "ModulePlayer.h"

#include <iostream>
using namespace std;

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"

#include "SDL/include/SDL_render.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// Idle animation - just one sprite
	idleDAnim.Empty();
	idleDAnim.PushBack({ 128, 32, 16, 16 });
	idleURAnim.PushBack({ 144, 32, 16, 16 });
	idleLRAnim.PushBack({ 160, 32, 16, 16 });
	idleULAnim.PushBack({ 176, 32, 16, 16 });
	idleUAnim.PushBack({ 192, 32, 16, 16 });
	//nome cames

	// Move upwards
	downAnim.Empty();
	downAnim.PushBack({ 0, 32, 16, 16 });
	downAnim.PushBack({ 16, 32, 16, 16 });
	downAnim.PushBack({ 32, 32, 16, 16 });
	downAnim.PushBack({ 48, 32, 16, 16 });
	downAnim.PushBack({ 64, 32, 16, 16 });
	downAnim.PushBack({ 80, 32, 16, 16 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Move down
	upAnim.Empty();
	upAnim.PushBack({ 0, 0, 16, 16 });
	upAnim.PushBack({ 16, 0, 16, 16 });
	upAnim.PushBack({ 32, 0, 16, 16 });
	upAnim.PushBack({ 48, 0, 16, 16 });
	upAnim.PushBack({ 64, 0, 16, 16 });
	upAnim.PushBack({ 80, 0, 16, 16 });
	upAnim.PushBack({ 96, 0, 16, 16 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	//Move rigth 
	rigthAnim.Empty(); 
	rigthAnim.PushBack({ 0, 16, 16, 16 });
	rigthAnim.PushBack({ 16, 16, 16, 16 });
	rigthAnim.PushBack({ 32, 16, 16, 16 });
	rigthAnim.PushBack({ 48, 16, 16, 16 });
	rigthAnim.PushBack({ 64, 16, 16, 16 });
	rigthAnim.PushBack({ 80, 16, 16, 16 });
	rigthAnim.PushBack({ 96, 16, 16, 16 });
	rigthAnim.loop = true;
	rigthAnim.speed = 0.1f;

	//Move left
	leftAnim.Empty();
	leftAnim.PushBack({ 0, 208, 16, 16 });
	leftAnim.PushBack({ 16, 208, 16, 16 });
	leftAnim.PushBack({ 32, 208, 16, 16 });
	leftAnim.PushBack({ 48, 208, 16, 16 });
	leftAnim.PushBack({ 64, 208, 16, 16 });
	leftAnim.PushBack({ 80, 208, 16, 16 });
	leftAnim.PushBack({ 96, 208, 16, 16 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	//Diagonal Secundaria
	diagonalSAnim.Empty(); 
	diagonalSAnim.PushBack({ 128, 0, 16, 16 });
	diagonalSAnim.PushBack({ 144, 0, 16, 16 });
	diagonalSAnim.PushBack({ 160, 0, 16, 16 });
	diagonalSAnim.PushBack({ 176, 0, 16, 16 });
	diagonalSAnim.PushBack({ 192, 0, 16, 16 });
	diagonalSAnim.PushBack({ 208, 0, 16, 16 });
	diagonalSAnim.loop = true;
	diagonalSAnim.speed = 0.1f;

	//Diagonal Principal
	diagonalPAnim.Empty(); 
	diagonalPAnim.PushBack({ 128, 16, 16, 16 });
	diagonalPAnim.PushBack({ 144, 16, 16, 16 });
	diagonalPAnim.PushBack({ 160, 16, 16, 16 });
	diagonalPAnim.PushBack({ 176, 16, 16, 16 });
	diagonalPAnim.PushBack({ 192, 16, 16, 16 });
	diagonalPAnim.PushBack({ 208, 16, 16, 16 });
	diagonalPAnim.PushBack({ 224, 16, 16, 16 });
	diagonalPAnim.loop = true;
	diagonalPAnim.speed = 0.1f;

	//Diagonal Secundaria Reverse
	
	diagonalSRAnim.Empty();
	diagonalSRAnim.PushBack({ 0, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 16, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 32, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 48, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 64, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 80, 224, 16, 16 });
	diagonalSRAnim.loop = true;
	diagonalSRAnim.speed = 0.1f;

	//Diagonal Principal Reverse
	diagonalPRAnim.Empty();
	diagonalPRAnim.PushBack({ 0, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 16, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 32, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 48, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 64, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 80, 240, 16, 16 });
	diagonalPRAnim.PushBack({ 96, 240, 16, 16 });
	diagonalPRAnim.loop = true;
	diagonalPRAnim.speed = 0.1f;


	//ANIMACIONS TOP HOME
	topDownAnim.Empty();
	topDownAnim.PushBack({ 0, 48, 32, 32 });
	topDRAnim.PushBack({ 32, 48, 32, 32 });
	topDLAnim.PushBack({ 112, 208, 32, 32});
	topLeftAnim.PushBack({ 144, 208, 32, 32 });
	topRightAnim.PushBack({ 64, 48, 32, 32 });
	topURAnim.PushBack({ 96, 48, 32, 32 });
	topULAnim.PushBack({ 176, 208, 32, 32});
	topUpAnim.PushBack({ 128, 48, 32, 32 });
	
	//ANIMACIONS DISPARANT TOP HOME
	shootDownAnim.Empty();
	shootDownAnim.PushBack({ 160, 48, 32, 32 });
	shootDRAnim.PushBack({ 192, 48, 32, 32 });
	shootDLAnim.PushBack({ 256, 48, 32, 32 });
	shootLeftAnim.PushBack({ 288, 48, 32, 32 });
	shootRightAnim.PushBack({ 224, 48, 32, 32 });
	shootURAnim.PushBack({ 0, 80, 32, 32 });
	shootULAnim.PushBack({ 256, 80, 32, 32 });
	shootUpAnim.PushBack({ 32, 80, 32, 32 });
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/SpritesSSTV/Entity_Player.png");
	currentAnimation = &idleUAnim;
	currentTopAnimation = &topDownAnim;

	textureDoorTop = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_Portes.png");

	textureUI = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV_UI.png");

	textureFont = App->textures->Load("Assets/SpritesSSTV/Font.png"); //Font

	textureMort = App->textures->Load("Assets/SpritesSSTV/Game_Over.png"); //Mort

	texturePickups = App->textures->Load("Assets/SpritesSSTV/Entity_Projectiles_and_gift.png");

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	Coin = App->audio->LoadFx("Assets/Audio/SFX/Money.wav");
	

	position.x = 150;
	position.y = 120;

	bandera_trip = false;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 25, 35 }, Collider::Type::PLAYER, this);

	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	if (App->input->keys[SDL_SCANCODE_F2] == KeyState::KEY_DOWN) {
		bandera_GodMode = !bandera_GodMode;
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KeyState::KEY_DOWN) {
		App->sceneLevel_1->sceneTimer = 3600;
	}

	if (App->input->keys[SDL_SCANCODE_F] == KeyState::KEY_DOWN) {
		bandera_trip = true;
		cont_Tripel = 1000000;
	}


	//Preguntar pk no funciona el martes
	if (bandera_GodMode == false) {
		if (((App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) || pad.left_x < 0.0f) && position.x >= 28) //LEFT
		{
			position.x -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) || pad.left_y < 0.0f) { //LEFT UP
				diagonal = true;
				if (currentAnimation != &diagonalPRAnim)
				{
					diagonalPRAnim.Reset();
					currentAnimation = &diagonalPRAnim;

					if (shooting == false) {
						topULAnim.Reset();
						currentTopAnimation = &topULAnim;
					}
				}
			}

			if ((currentAnimation != &leftAnim) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

				if (shooting == false) {
					topLeftAnim.Reset();
					currentTopAnimation = &topLeftAnim;
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) || pad.left_x > 0.0f) && position.x <= 455) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) || pad.left_y > 0.0f) { //DOWN RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalPAnim)
				{
					diagonalPAnim.Reset();
					currentAnimation = &diagonalPAnim;

					if (shooting == false) {
						topDRAnim.Reset();
						currentTopAnimation = &topDRAnim;
					}
				}
			}

			if (currentAnimation != &rigthAnim && (diagonal == false))
			{
				rigthAnim.Reset();
				currentAnimation = &rigthAnim;

				if (shooting == false) {
					topRightAnim.Reset();
					currentTopAnimation = &topRightAnim;
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) || pad.left_y > 0.0f) && position.y <= 390) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) || pad.left_x < 0.0f) { //DOWN LEFT
				diagonal = true;
				if (currentAnimation != &diagonalSRAnim)
				{
					diagonalSRAnim.Reset();
					currentAnimation = &diagonalSRAnim;

					if (shooting == false) {
						topDLAnim.Reset();
						currentTopAnimation = &topDLAnim;
					}
				}
			}

			if (currentAnimation != &downAnim && (diagonal == false))
			{
				downAnim.Reset();
				currentAnimation = &downAnim;

				if (shooting == false) {
					topDownAnim.Reset();
					currentTopAnimation = &topDownAnim;
				}
			}
		}

		if (((App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) || pad.left_y > 0.0f) && position.y >= 60) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) || pad.left_x > 0.0f) { // UP RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalSAnim)
				{
					diagonalSAnim.Reset();
					currentAnimation = &diagonalSAnim;

					if (shooting == false) {
						topURAnim.Reset();
						currentTopAnimation = &topURAnim;
					}
				}
			}

			if (currentAnimation != &upAnim && (diagonal == false))
			{
				upAnim.Reset();
				currentAnimation = &upAnim;

				if (shooting == false) {
					topUpAnim.Reset();
					currentTopAnimation = &topUpAnim;
				}
			}
		}

		if (MovKeyPressed < 2) {
			diagonal = false;
		}
		MovKeyPressed = 0;
	}
	if (bandera_GodMode == true) {
		if ((App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) || pad.left_x < 0.0f) //LEFT
		{
			position.x -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) || pad.left_y > 0.0f) { //LEFT UP
				diagonal = true;
				if (currentAnimation != &diagonalPRAnim)
				{
					diagonalPRAnim.Reset();
					currentAnimation = &diagonalPRAnim;

					if (shooting == false) {
						topULAnim.Reset();
						currentTopAnimation = &topULAnim;
					}
				}
			}

			if ((currentAnimation != &leftAnim) && (diagonal == false)) //ANIMACIÓ LEFT
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;

				if (shooting == false) {
					topLeftAnim.Reset();
					currentTopAnimation = &topLeftAnim;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) || pad.left_x > 0.0f) //RIGHT
		{
			position.x += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) || pad.left_y < 0.0f) { //DOWN RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalPAnim)
				{
					diagonalPAnim.Reset();
					currentAnimation = &diagonalPAnim;

					if (shooting == false) {
						topDRAnim.Reset();
						currentTopAnimation = &topDRAnim;
					}
				}
			}

			if (currentAnimation != &rigthAnim && (diagonal == false))
			{
				rigthAnim.Reset();
				currentAnimation = &rigthAnim;

				if (shooting == false) {
					topRightAnim.Reset();
					currentTopAnimation = &topRightAnim;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) || pad.left_y < 0.0f) //DOWN
		{
			position.y += speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) || pad.left_x > 0.0f) { //DOWN LEFT
				diagonal = true;
				if (currentAnimation != &diagonalSRAnim)
				{
					diagonalSRAnim.Reset();
					currentAnimation = &diagonalSRAnim;

					if (shooting == false) {
						topDLAnim.Reset();
						currentTopAnimation = &topDLAnim;
					}
				}
			}

			if (currentAnimation != &downAnim && (diagonal == false))
			{
				downAnim.Reset();
				currentAnimation = &downAnim;

				if (shooting == false) {
					topDownAnim.Reset();
					currentTopAnimation = &topDownAnim;
				}
			}
		}

		if ((App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) || pad.left_y > 0.0f) //UP
		{
			position.y -= speed;
			++MovKeyPressed;

			if ((App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) || pad.left_x < 0.0f) { // UP RIGHT
				diagonal = true;
				if (currentAnimation != &diagonalSAnim)
				{
					diagonalSAnim.Reset();
					currentAnimation = &diagonalSAnim;

					if (shooting == false) {
						topURAnim.Reset();
						currentTopAnimation = &topURAnim;
					}
				}
			}

			if (currentAnimation != &upAnim && (diagonal == false))
			{
				upAnim.Reset();
				currentAnimation = &upAnim;

				if (shooting == false) {
					topUpAnim.Reset();
					currentTopAnimation = &topUpAnim;
				}
			}
		}

		if (MovKeyPressed < 2) {
			diagonal = false;
		}
		MovKeyPressed = 0;
	}

	if (bandera_trip == true)
	{
		cont_Tripel--;
	}
	//Direccion de donde va la bala
		//DIAGONALS
	cont++;
	if (cont >= 10) { //DELAY
		bandera = true;
		cont = 0;
	}
	else {
		bandera = false;
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT 
		|| (pad.right_x > 0.0f)
		|| (pad.right_x < 0.0f)
		|| (pad.right_y > 0.0f)
		|| (pad.right_y < 0.0f))
	{
		shooting = true;
	}
	else {
		shooting = false;
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT) //drt, amunt
	{
		shootURAnim.Reset();
		currentTopAnimation = &shootURAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = 3;
				App->particles->TripleShoot.speed.x = 3;
				App->particles->TripleShoot1.speed.x = 2;
				App->particles->TripleShoot1.speed.y = 4;
				App->particles->TripleShoot2.speed.x = 4;
				App->particles->TripleShoot2.speed.y = 2;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + 5, position.y + -16, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + 7, position.y + -15, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + 9, position.y - 14, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserUR, position.x + 7, position.y - 12, 6, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT) //Esq, amunt
	{
		shootULAnim.Reset();
		currentTopAnimation = &shootULAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = 3;
				App->particles->TripleShoot.speed.x = -3;
				App->particles->TripleShoot1.speed.x = -2;
				App->particles->TripleShoot1.speed.y = 4;
				App->particles->TripleShoot2.speed.x = -4;
				App->particles->TripleShoot2.speed.y = 2;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + -8, position.y + -12, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + -10, position.y + -11, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + -12, position.y + -10, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserUL, position.x - 5, position.y - 10, 5, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) //Esq, avall
	{
		shootDLAnim.Reset();
		currentTopAnimation = &shootDLAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = -3;
				App->particles->TripleShoot.speed.x = -3;
				App->particles->TripleShoot1.speed.x = -2;
				App->particles->TripleShoot1.speed.y = -4;
				App->particles->TripleShoot2.speed.x = -4;
				App->particles->TripleShoot2.speed.y = -2;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + -8, position.y + 12, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + -10, position.y + 11, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + -12, position.y + 10, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserDL, position.x - 12, position.y + 11, 7, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) //drt, avall
	{
		shootDRAnim.Reset();
		currentTopAnimation = &shootDRAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = -3;
				App->particles->TripleShoot.speed.x = 3;
				App->particles->TripleShoot1.speed.x = 2;
				App->particles->TripleShoot1.speed.y = -4;
				App->particles->TripleShoot2.speed.x = 4;
				App->particles->TripleShoot2.speed.y = -2;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + 5, position.y + 12, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + 7, position.y + 11, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + 9, position.y + 10, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserDR, position.x + 8, position.y + 8, 8, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	//RECTES
	else if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT) //amunt
	{
		shootUpAnim.Reset();
		currentTopAnimation = &shootUpAnim;

		if (bandera) {
			if(bandera_trip && cont_Tripel > 0)
			{
			App->particles->TripleShoot.speed.y = 5;
			App->particles->TripleShoot.speed.x = 0;
			App->particles->TripleShoot1.speed.x = 1;
			App->particles->TripleShoot1.speed.y = 5;
			App->particles->TripleShoot2.speed.x = -1;
			App->particles->TripleShoot2.speed.y = 5;

			App->particles->AddParticle(App->particles->TripleShoot, position.x + -2, position.y - 7, 6, Collider::Type::PLAYER_SHOT);		
			App->particles->AddParticle(App->particles->TripleShoot1, position.x + 1, position.y - 7, 6, Collider::Type::PLAYER_SHOT);
			App->particles->AddParticle(App->particles->TripleShoot2, position.x + -5, position.y - 7, 6, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			cont = 0;
			}
			else
			{
				App->particles->AddParticle(App->particles->laserU, position.x + -2, position.y + -7, 1, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
		}

	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT) //Esq
	{
		shootLeftAnim.Reset();
		currentTopAnimation = &shootLeftAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = 0;
				App->particles->TripleShoot.speed.x = -5;
				App->particles->TripleShoot1.speed.x = -5;
				App->particles->TripleShoot1.speed.y = -1;
				App->particles->TripleShoot2.speed.x = -5;
				App->particles->TripleShoot2.speed.y = 1;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + -20, position.y + 4, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + -20, position.y + 1, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + -20, position.y - 2, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserL, position.x - 10, position.y + 1, 2, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) // avall
	{
		shootDownAnim.Reset();
		currentTopAnimation = &shootDownAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = -5;
				App->particles->TripleShoot.speed.x = -0;
				App->particles->TripleShoot1.speed.x = -1;
				App->particles->TripleShoot1.speed.y = -5;
				App->particles->TripleShoot2.speed.x = 1;
				App->particles->TripleShoot2.speed.y = -5;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + -3, position.y + 15, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + 0, position.y + 15, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + 3, position.y + 15, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserD, position.x + 5, position.y + 15, 4, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT) //drt
	{
		shootRightAnim.Reset();
		currentTopAnimation = &shootRightAnim;

		if (bandera) {
			if (bandera_trip && cont_Tripel > 0)
			{
				App->particles->TripleShoot.speed.y = 0;
				App->particles->TripleShoot.speed.x = 5;
				App->particles->TripleShoot1.speed.x = 5;
				App->particles->TripleShoot1.speed.y = -1;
				App->particles->TripleShoot2.speed.x = 5;
				App->particles->TripleShoot2.speed.y = 1;

				App->particles->AddParticle(App->particles->TripleShoot1, position.x + 20, position.y + 4, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot, position.x + 20, position.y + 1, 6, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->TripleShoot2, position.x + 20, position.y + -2, 6, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(laserFx);
				cont = 0;
			}
			else
			{
			App->particles->AddParticle(App->particles->laserR, position.x + 10, position.y + 1, 3, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
			}
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_IDLE) {
		
		currentAnimation = &idleUAnim;
		if (!shooting) {
			currentTopAnimation = &topDownAnim;
		}
	}

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	currentTopAnimation->Update();

	//Gestió Array de la font
	scoreCopia = score;
	
	for (int i = 0; i < 8; ++i) {
		scoreN[i] = scoreCopia % 10;
		scoreCopia /= 10;
	}

	--contadorVides;
	if (contadorVides < -100) {
		contadorVides = -1;
	}

	if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_DOWN)
	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel2, 20);


	if (App->input->keys[SDL_SCANCODE_F5] == KeyState::KEY_DOWN) { //necessita col·lidir amb un enemic al final per morir
		vides--;
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN)
	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 20);

	if (pad.enabled)
	{
		if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentAnimation = &idleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_IDLE &&
		App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_IDLE) currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	//TOTA L'IMPRESSIÓ D'SPRITES DE NOMBRES I IMMUNITAT S'HA PORTAT AL ModuleEnemies, ara ja estan en ordre.

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->DrawTexture(texture, position.x + 2, position.y + 17, &rect, 1.5f);

	SDL_Rect rectTop = currentTopAnimation->GetCurrentFrame();
	App->render->DrawTexture(texture, position.x - 10, position.y - 7, &rectTop, 1.5f);

	//Render Portes
	App->render->DrawTexture(textureDoorTop, -512 * topDoor, 0, nullptr);
	//Si no li enviem rectangle (li enviem un 'nullptr'), es posa la mateixa mida que la pantalla.

	//Render UI
	App->render->DrawTexture(textureUI, 0, 0, nullptr);

	//Render Vides
	SDL_Rect rect0v = { 0, 16, 10, 14 };
	SDL_Rect rect1v = { 10, 16, 10, 14 };
	SDL_Rect rect2v = { 20, 16, 10, 14 };
	SDL_Rect rect3v = { 30, 16, 10, 14 };
	SDL_Rect rect4v = { 40, 16, 10, 14 };
	SDL_Rect rect5v = { 50, 16, 10, 14 };
	SDL_Rect rect6v = { 60, 16, 10, 14 };
	SDL_Rect rect7v = { 70, 16, 10, 14 };
	SDL_Rect rect8v = { 80, 16, 10, 14 };
	SDL_Rect rect9v = { 90, 16, 10, 14 };
	SDL_Rect rect10v = { 0, 0, 512, 512 };

	switch (vides) {
	case 0:
		App->render->DrawTexture(textureFont, 43, 54, &rect0v, 1.5f);
		break;
	case 1:
		App->render->DrawTexture(textureFont, 43, 54, &rect1v, 1.5f);
		break;
	case 2:
		App->render->DrawTexture(textureFont, 43, 54, &rect2v, 1.5f);
		break;
	case 3:
		App->render->DrawTexture(textureFont, 43, 54, &rect3v, 1.5f);
		break;
	case 4:
		App->render->DrawTexture(textureFont, 43, 54, &rect4v, 1.5f);
		break;
	case 5:
		App->render->DrawTexture(textureFont, 43, 54, &rect5v, 1.5f);
		break;
	case 6:
		App->render->DrawTexture(textureFont, 43, 54, &rect6v, 1.5f);
		break;
	case 7:
		App->render->DrawTexture(textureFont, 43, 54, &rect7v, 1.5f);
		break;
	case 8:
		App->render->DrawTexture(textureFont, 43, 54, &rect8v, 1.5f);
		break;
	case 9:
		App->render->DrawTexture(textureFont, 43, 54, &rect9v, 1.5f);
		break;
	}

	if (App->input->keys[SDL_SCANCODE_P] == KeyState::KEY_DOWN)
	{
		shootRightAnim.Reset();
		currentTopAnimation = &shootRightAnim;
		if (bandera) {
			App->particles->AddParticle(App->particles->laserR, position.x + 10, position.y + 1, 3, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
	}

	if(vides <= 0)
	{
		App->render->DrawTexture(textureMort, 0, 0, &rect10v, 1);
		//App->pause = true;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{		//Falta cambiar el sumatori de punts segons el tipus de objecte que agafes
	if (c2->type == c2->object_gold)
	{
		App->audio->PlayFx(Coin);
		money += 100;
	}
	if (c2->type == c2->object_silver)
	{
		App->audio->PlayFx(Coin);
		money += 50;
	}
	if (c2->type == c2->object_silver_gold)
	{
		App->audio->PlayFx(Coin);
		money += 75;
	}
	if (c2->type == c2->object_money)
	{
		App->audio->PlayFx(Coin);
		money += 5;
	}
	
	if (c2->type == c2->object_Triple)
	{
		bandera_trip = true;
		cont_Tripel = 500;
	}	
	
	if (c2->type == c2->object_Vida)
	{
		vides++;
	}

	if (c2->type == c2->Door && App->sceneLevel_1->sceneTimer >= 3600 && App->enemies->enemyNum == 0) {
		//	WIN CONDITION
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneSwap, 0); //sceneWin, sceneSwap
	}
	
	//GESTIONAR LES VIDES I LA MORT
	if ((c2->type == c2->ENEMY) && (contadorVides < 0) && (bandera_GodMode == false) && (destroyed == false)) {

		if (vides > 0) {
			--vides;
		}
		else if (vides <= 0) {		//FALTA PULIR MOLTISSIM!!!!!
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, 0, Collider::Type::NONE, 9);
			App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, 0, Collider::Type::NONE, 14);
			App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, 0, Collider::Type::NONE, 40);
			App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, 0, Collider::Type::NONE, 28);
			App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, 0, Collider::Type::NONE, 21);

			App->audio->PlayFx(explosionFx);


			App->pause = true;

			//App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->SceneLevel2, 20);
			
			destroyed = false;
		}
		contadorVides = 50; //50 frames de delay
	}
}

bool ModulePlayer::CleanUp() {
	
	LOG("Freeing player");

	//desinicialitzar tots els sprites
	App->textures->Unload(texture);
	App->textures->Unload(textureDoorTop);
	App->textures->Unload(textureUI);
	App->textures->Unload(textureFont);
	App->textures->Unload(textureMort);
	App->textures->Unload(texturePickups);

	//App->audio->CleanFX(laserFx);

	return true;
}