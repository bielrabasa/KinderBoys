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

	//Move rigth  (left es igual invertit) 
	rigthAnim.PushBack({ 0, 16, 16, 16 });
	rigthAnim.PushBack({ 16, 16, 16, 16 });
	rigthAnim.PushBack({ 32, 16, 16, 16 });
	rigthAnim.PushBack({ 48, 16, 16, 16 });
	rigthAnim.PushBack({ 64, 16, 16, 16 });
	rigthAnim.PushBack({ 80, 16, 16, 16 });
	rigthAnim.PushBack({ 96, 16, 16, 16 });
	rigthAnim.loop = true;
	rigthAnim.speed = 0.1f;

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

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	position.y = 120;

	// L10: TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

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
			if (currentAnimation != &diagonalPAnim)
			{
				diagonalPAnim.Reset();
				currentAnimation = &diagonalPAnim;
			}
		}
		
		if ((currentAnimation != &rigthAnim) && (diagonal == false)) //ANIMACIÓ LEFT
		{
			rigthAnim.Reset();
			currentAnimation = &rigthAnim;

			//cambiar rigthAnim por leftAnim que es el mismo pero invertido
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
			}
		}
				
		if (currentAnimation != &rigthAnim && (diagonal == false))
		{
			rigthAnim.Reset();
			currentAnimation = &rigthAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT) //DOWN
	{
		position.y += speed;
		++MovKeyPressed;

		if (App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT) { //DOWN LEFT
			diagonal = true;
			if (currentAnimation != &diagonalSAnim)
			{
				diagonalSAnim.Reset();
				currentAnimation = &diagonalSAnim;
			}
		}

		if (currentAnimation != &downAnim && (diagonal == false))
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
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
			}
		}

		if (currentAnimation != &upAnim && (diagonal == false))
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (MovKeyPressed < 2) {
		diagonal = false;
	}
	MovKeyPressed = 0;

	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_IDLE)
		currentAnimation = &idleUAnim;

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x, position.y, &rect);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == collider) && (destroyed == false))
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		// L10: TODO 3: Go back to the intro scene when the player gets killed

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}