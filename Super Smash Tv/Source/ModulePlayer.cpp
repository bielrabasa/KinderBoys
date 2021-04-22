#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// Idle animation - just one sprite
	idleDAnim.PushBack({ 128, 32, 16, 16 });
	idleURAnim.PushBack({ 144, 32, 16, 16 });
	idleLRAnim.PushBack({ 160, 32, 16, 16 });
	idleULAnim.PushBack({ 176, 32, 16, 16 });
	idleUAnim.PushBack({ 192, 32, 16, 16 });
	//nome cames

	// Move upwards
	downAnim.PushBack({ 0, 32, 16, 16 });
	downAnim.PushBack({ 16, 32, 16, 16 });
	downAnim.PushBack({ 32, 32, 16, 16 });
	downAnim.PushBack({ 48, 32, 16, 16 });
	downAnim.PushBack({ 64, 32, 16, 16 });
	downAnim.PushBack({ 80, 32, 16, 16 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Move down
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
	diagonalSAnim.PushBack({ 128, 0, 16, 16 });
	diagonalSAnim.PushBack({ 144, 0, 16, 16 });
	diagonalSAnim.PushBack({ 160, 0, 16, 16 });
	diagonalSAnim.PushBack({ 176, 0, 16, 16 });
	diagonalSAnim.PushBack({ 192, 0, 16, 16 });
	diagonalSAnim.PushBack({ 208, 0, 16, 16 });
	diagonalSAnim.loop = true;
	diagonalSAnim.speed = 0.1f;

	//Diagonal Principal
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
	diagonalSRAnim.PushBack({ 0, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 16, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 32, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 48, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 64, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 80, 224, 16, 16 });
	diagonalSRAnim.PushBack({ 96, 224, 16, 16 });
	diagonalSRAnim.loop = true;
	diagonalSRAnim.speed = 0.1f;

	//Diagonal Principal Reverse
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
	topDownAnim.PushBack({ 0, 48, 32, 32 });
	topDRAnim.PushBack({ 32, 48, 32, 32 });
	topDLAnim.PushBack({ 112, 208, 32, 32});
	topLeftAnim.PushBack({ 144, 208, 32, 32 });
	topRightAnim.PushBack({ 64, 48, 32, 32 });
	topURAnim.PushBack({ 96, 48, 32, 32 });
	topULAnim.PushBack({ 176, 208, 32, 32});
	topUpAnim.PushBack({ 128, 48, 32, 32 });
	
	//ANIMACIONS DISPARANT TOP HOME
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

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	// L10: TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 48 }, Collider::Type::PLAYER, this);

	//GodMode

	if (App->input->keys[SDL_SCANCODE_F5] == KeyState::KEY_DOWN) {
		collider = App->collisions->AddCollider({ position.x, position.y, 0, 0 }, Collider::Type::PLAYER, this);
	}
	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.x += 0;

	if (App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) //LEFT
	{
		position.x -= speed;
		++MovKeyPressed;

		if (App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) { //LEFT UP
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

	 if (App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) //RIGHT
	{
		position.x += speed;
		++MovKeyPressed;

		if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) { //DOWN RIGHT
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

	 if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) //DOWN
	{
		position.y += speed;
		++MovKeyPressed;

		if (App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) { //DOWN LEFT
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

	 if (App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT) //UP
	{
		position.y -= speed;
		++MovKeyPressed;

		if (App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT) { // UP RIGHT
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


	//Direccion de donde va la bala
		//DIAGONALS
	cont++;
	if (cont >= 25) { //DELAY
		bandera = true;
		cont = 0;
	}
	else {
		bandera = false;
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
		|| App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) 
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
			App->particles->AddParticle(App->particles->laser, position.x + 20, position.y - 20, 6, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	else if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT) //Esq, amunt
	{
		shootULAnim.Reset();
		currentTopAnimation = &shootULAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x - 20, position.y - 20, 5, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) //Esq, avall
	{
		shootDLAnim.Reset();
		currentTopAnimation = &shootDLAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x - 20, position.y + 20, 7, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) //drt, avall
	{
		shootDRAnim.Reset();
		currentTopAnimation = &shootDRAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x + 20, position.y + 20, 8, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	//RECTES
	else if (App->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT) //amunt
	{
		shootUpAnim.Reset();
		currentTopAnimation = &shootUpAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x, position.y - 20, 1, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
			cont = 0;
		}

	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT) //Esq
	{
		shootLeftAnim.Reset();
		currentTopAnimation = &shootLeftAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x - 20, position.y, 2, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	else if (App->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT) // avall
	{
		shootDownAnim.Reset();
		currentTopAnimation = &shootDownAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x, position.y + 20, 4, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
		}
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT) //drt
	{
		shootRightAnim.Reset();
		currentTopAnimation = &shootRightAnim;

		if (bandera) {
			App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, 3, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(laserFx);
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

	

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x, position.y, &rect);
		
		SDL_Rect rectTop = currentTopAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x - 8, position.y - 16, &rectTop);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == collider) && (destroyed == false))
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y,0, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11,0, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12,0, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5,0, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4,0,Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		// L10: TODO 3: Go back to the intro scene when the player gets killed

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}