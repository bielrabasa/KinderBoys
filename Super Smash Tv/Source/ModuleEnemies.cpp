#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h" //Per arreglar l'error
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_Mech.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/SpritesSSTV/Entity_Green_and_Pink.png");

	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	textureFont = App->textures->Load("Assets/SpritesSSTV/Font.png");

	return true;
}

UpdateResult ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleEnemies::PostUpdate()
{
	
	//Render PressToPlay
	SDL_Rect rectPTP = { 0, 30, 70, 32 };
	App->render->DrawTexture(App->player->textureFont, 353, 98, &rectPTP);

	//Render Font
	SDL_Rect rect0 = { 0, 0, 10, 16 };
	SDL_Rect rect1 = { 10, 0, 10, 16 };
	SDL_Rect rect2 = { 20, 0, 10, 16 };
	SDL_Rect rect3 = { 30, 0, 10, 16 };
	SDL_Rect rect4 = { 40, 0, 10, 16 };
	SDL_Rect rect5 = { 50, 0, 10, 16 };
	SDL_Rect rect6 = { 60, 0, 10, 16 };
	SDL_Rect rect7 = { 70, 0, 10, 16 };
	SDL_Rect rect8 = { 80, 0, 10, 16 };
	SDL_Rect rect9 = { 90, 0, 10, 16 };


	for (int i = 0; i < 8; ++i) {

		switch (App->player->scoreN[i]) {
		case 0:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect0);
			break;
		case 1:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect1);
			break;
		case 2:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect2);
			break;
		case 3:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect3);
			break;
		case 4:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect4);
			break;
		case 5:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect5);
			break;
		case 6:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect6);
			break;
		case 7:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect7);
			break;
		case 8:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect8);
			break;
		case 9:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect9);
			break;
		}

		posicioFont -= 15; //Separació entre nombres
	}
	posicioFont = 160; //Posició del primer element de la dreta
	
	//Render Immunitat
	SDL_Rect rectImmun = { 96, 56, 32, 32 };
	if (App->player->contadorVides > 0 && App->player->contadorVides % 3 == 0) {
		App->render->DrawTexture(App->player->texturePickups, App->player->position.x - 11, App->player->position.y + 10, &rectImmun);
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y);
					break;
				case Enemy_Type::BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y);
					break;
				case Enemy_Type::MECH:
					enemies[i] = new Enemy_Mech(info.x, info.y);
					break;
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}