#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"

#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::Door] = false;
	matrix[Collider::Type::WALL][Collider::Type::object_gold] = false;
	matrix[Collider::Type::WALL][Collider::Type::object_silver] = false;
	matrix[Collider::Type::WALL][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::WALL][Collider::Type::object_money] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::Door] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::object_gold] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::object_silver] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::object_silver_gold] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::object_money] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::Door] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::object_gold] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::object_silver] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::object_money] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::Door] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::object_gold] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::object_silver] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::object_money] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::Door] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::object_gold] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::object_silver] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::object_money] = false;

	matrix[Collider::Type::Door][Collider::Type::WALL] = false;
	matrix[Collider::Type::Door][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::Door][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::Door][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::Door][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::Door][Collider::Type::Door] = false;
	matrix[Collider::Type::Door][Collider::Type::object_gold] = false;
	matrix[Collider::Type::Door][Collider::Type::object_silver] = false;
	matrix[Collider::Type::Door][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::Door][Collider::Type::object_money] = false;

	matrix[Collider::Type::object_gold][Collider::Type::object_gold] = false;
	matrix[Collider::Type::object_gold][Collider::Type::WALL] = false;
	matrix[Collider::Type::object_gold][Collider::Type::Door] = false;
	matrix[Collider::Type::object_gold][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::object_gold][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::object_gold][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::object_gold][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::object_gold][Collider::Type::object_silver] = false;
	matrix[Collider::Type::object_gold][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::object_gold][Collider::Type::object_money] = false;

	matrix[Collider::Type::object_silver][Collider::Type::object_silver] = false;
	matrix[Collider::Type::object_silver][Collider::Type::WALL] = false;
	matrix[Collider::Type::object_silver][Collider::Type::Door] = false;
	matrix[Collider::Type::object_silver][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::object_silver][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::object_silver][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::object_silver][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::object_silver][Collider::Type::object_gold] = false;
	matrix[Collider::Type::object_silver][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::object_silver][Collider::Type::object_money] = false;

	matrix[Collider::Type::object_silver_gold][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::object_silver] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::object_gold] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::object_silver_gold][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::WALL] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::Door] = false;
	matrix[Collider::Type::object_silver_gold][Collider::Type::object_money] = false;

	matrix[Collider::Type::object_money][Collider::Type::object_money] = false;
	matrix[Collider::Type::object_money][Collider::Type::object_gold] = false;
	matrix[Collider::Type::object_money][Collider::Type::object_silver] = false;
	matrix[Collider::Type::object_money][Collider::Type::object_silver_gold] = false;
	matrix[Collider::Type::object_money][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::object_money][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::object_money][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::object_money][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::object_money][Collider::Type::WALL] = false;
	matrix[Collider::Type::object_money][Collider::Type::Door] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

UpdateResult ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// Skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		debug = !debug;
	}

	//El otro GodMode que tampoco funciona :)
	/*if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		if (bandera_GodMode == false) {
			bandera_GodMode = true;
		}
		if (bandera_GodMode == true) {
			bandera_GodMode = false;
		}
	}
	if (bandera_GodMode == false) {
		matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::Door] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::obejcts] = true;

		matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
		matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
		matrix[Collider::Type::Door][Collider::Type::PLAYER] = true;
		matrix[Collider::Type::obejcts][Collider::Type::PLAYER] = true;
	}
	if (bandera_GodMode == true) {
		matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::Door] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::obejcts] = false;

		matrix[Collider::Type::WALL][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::Door][Collider::Type::PLAYER] = false;
		matrix[Collider::Type::obejcts][Collider::Type::PLAYER] = false;
	}*/
	

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 255, alpha });
			break;
			case Collider::Type::WALL: // blue
			App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 0, 255, alpha });
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 0, alpha });
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 0, alpha });
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 255, 0, alpha });
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 255, alpha });
			break;
			case Collider::Type::Door: // azul claro
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 0, 255, 251, alpha });
			break;
			case Collider::Type::obejcts: // rosa
				App->render->DrawRectangle(colliders[i]->rect, SDL_Color{ 255, 0, 236, alpha });
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
