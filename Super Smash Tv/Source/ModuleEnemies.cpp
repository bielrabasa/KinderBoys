#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h" //Per arreglar l'error
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_Mech.h"
#include "SceneLevel1.h"
#include "level2.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

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

	enemyNum = 0;

	srand(time(NULL));

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

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KeyState::KEY_REPEAT)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i) {
			enemyNum--;

			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	HandleEnemiesDespawn();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleEnemies::PostUpdate()
{
	
	//Render PressToPlay
	SDL_Rect rectPTP = { 0, 30, 70, 32 };
	App->render->DrawTexture(App->player->textureFont, 353, 98, &rectPTP, 1.5f);

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
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect0, 1.5f);
			break;
		case 1:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect1, 1.5f);
			break;
		case 2:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect2, 1.5f);
			break;
		case 3:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect3, 1.5f);
			break;
		case 4:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect4, 1.5f);
			break;
		case 5:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect5, 1.5f);
			break;
		case 6:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect6, 1.5f);
			break;
		case 7:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect7, 1.5f);
			break;
		case 8:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect8, 1.5f);
			break;
		case 9:
			App->render->DrawTexture(textureFont, posicioFont, 100, &rect9, 1.5f);
			break;
		}

		posicioFont -= 15; //Separació entre nombres
	}
	posicioFont = 160; //Posició del primer element de la dreta
	

	//IMPRIMIR RECTANGLES VERMELL TRIPLE SHOT
	//SDL_Rect rectTempos1 = { -202, 75, 14, 4 }; //Quan està en finestra
	SDL_Rect rectTempos1 = { 48, 125, 14, 4};
	App->render->DrawRectangle(rectTempos1, SDL_Color{ 255, 0, 0, 255 }); //L'ultim 255 és opac
	
	SDL_Rect rectTempos2 = { 65, 125, 14, 4 };
	App->render->DrawRectangle(rectTempos2, SDL_Color{ 255, 0, 0, 255 });
	
	SDL_Rect rectTempos3 = { 82, 125, 14, 4 };
	App->render->DrawRectangle(rectTempos3, SDL_Color{ 255, 0, 0, 255 });
	
	SDL_Rect rectTempos4 = { 99, 125, 14, 4 };
	App->render->DrawRectangle(rectTempos4, SDL_Color{ 255, 0, 0, 255 });
	
	SDL_Rect rectTempos5 = { 116, 125, 14, 4 };
	App->render->DrawRectangle(rectTempos5, SDL_Color{ 255, 0, 0, 255 });
	
	SDL_Rect rectTempos6 = { 133, 125, 14, 4 };
	App->render->DrawRectangle(rectTempos6, SDL_Color{ 255, 0, 0, 255 });

	if (App->player->cont_Tripel > 0) {
		switch (App->player->cont_Tripel / 83) { //Dibuixa rectangles verds si el triple shot està actiu.
		case 6:
		case 5:
			App->render->DrawRectangle(rectTempos6, SDL_Color{ 0, 255, 0, 255 });
		case 4:
			App->render->DrawRectangle(rectTempos5, SDL_Color{ 0, 255, 0, 255 });
		case 3:
			App->render->DrawRectangle(rectTempos4, SDL_Color{ 0, 255, 0, 255 });
		case 2:
			App->render->DrawRectangle(rectTempos3, SDL_Color{ 0, 255, 0, 255 });
		case 1:
			App->render->DrawRectangle(rectTempos2, SDL_Color{ 0, 255, 0, 255 });
		case 0:
			App->render->DrawRectangle(rectTempos1, SDL_Color{ 0, 255, 0, 255 });
			break;
		}
	}
	//Render Immunitat
	SDL_Rect rectImmun = { 96, 56, 32, 32 };
	if (App->player->contadorVides > 0 && App->player->contadorVides % 3 == 0) {
		App->render->DrawTexture(App->player->texturePickups, App->player->position.x - 11, App->player->position.y + 10, &rectImmun, 1.5f);
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

	App->textures->Unload(texture);
	App->textures->Unload(textureFont);

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

			enemyNum++;

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
	//mira si estas a lvl1 per matar d'un tir
	if(App->sceneLevel_1->lvl1 == true && App->sceneLevel2->lvl2 == false){
		for(uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && ((c2->type == c2->PLAYER_SHOT)||(c2->type == c2->PLAYER_TRIPLE_SHOT)))
			{
				enemies[i]->OnCollision(c2); //Notify the enemy of a collision

				enemyNum--;

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
	//mira si estas a lvl2 per matar de7 hits
	else if(App->sceneLevel2->lvl2 == true && App->sceneLevel_1->lvl1 == false)
	{
		//cout << videsTorreta;
		if(videsTorreta > 0 && (c2->type == c2->PLAYER_SHOT) || ( c2->type == c2->PLAYER_TRIPLE_SHOT))
			videsTorreta--;

		if (videsTorreta == 0)
		{
			for (uint i = 0; i < MAX_ENEMIES; ++i)
			{
				if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && ((c2->type == c2->PLAYER_SHOT) || (c2->type == c2->PLAYER_TRIPLE_SHOT)))
				{
					enemies[i]->OnCollision(c2); //Notify the enemy of a collision

					enemyNum--;

					delete enemies[i];
					enemies[i] = nullptr;
					break;
				}
			}
		}
	}
}