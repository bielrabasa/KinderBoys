#include "SceneLevel1.h"

#include <time.h>
#include <stdlib.h>
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"


SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV.png");
	App->audio->PlayMusic("Assets/", 1.0f);

	App->enemies->Enable();
	App->particles->Enable();

	//Bottomside collider  Primer numero x, Segundo numero y, 3r numero largo del cubo, 4o anchura del cubo
	//Tendremos problemas con la hitbox y la entrada y salida tanto de personajes como de enemigos
	//Posible solucion un bool de enemigos vivos 
	App->collisions->AddCollider({ 0, 431,208, 16 }, Collider::Type::WALL);//Pared inferior-Parte izquierda
	App->collisions->AddCollider({ 312, 431,200, 16 }, Collider::Type::WALL);//Pared inferior-Parte derecha

	App->collisions->AddCollider({ 0, 16,208, 16 }, Collider::Type::WALL);//Pared Superior-Izquierda
	App->collisions->AddCollider({ 304, 16,512, 16 }, Collider::Type::WALL);//Pared Superior-derecha

	App->collisions->AddCollider({ 10, 0,16, 210 }, Collider::Type::WALL);//Pared lateral izquierdo-Superior
	App->collisions->AddCollider({ 10, 289,16, 448 }, Collider::Type::WALL);//Pared lateral izquierdo-Inferior

	App->collisions->AddCollider({ 492, 0,16, 210 }, Collider::Type::WALL);//Pared lateral derecho-Superior
	App->collisions->AddCollider({ 492, 289,16, 448 }, Collider::Type::WALL);//Pared lateral derecho-Inferior

	App->collisions->AddCollider({ 208, 16,96, 16 }, Collider::Type::Door);//Puerta Superior
	App->collisions->AddCollider({ 208, 431,104, 16 }, Collider::Type::Door);//Puerta inferior
	App->collisions->AddCollider({ 10, 210,16, 79 }, Collider::Type::Door);//Puerta izquierda
	App->collisions->AddCollider({ 492, 210,16, 79 }, Collider::Type::Door);//Puerta derecha


	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);


	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 100);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 450);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 50);

	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 150);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 250);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);

	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 750, 120);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 775, 120);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 790, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 300);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 400);

	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->vides = 5;
	App->player->score = 0;

	// L10: TODO 2: Enable (and properly disable) the player module
	App->player->Enable();

	srand(time(NULL));

	return ret;
}

UpdateResult SceneLevel1::Update()
{
	//App->render->camera.x += 3; //SCROLL
	++num;
	++sceneTimer;

	//if ((App->input->keys[SDL_SCANCODE_Q] == KeyState::KEY_REPEAT) && (App->player->vides > 0)) //SpawnShit
	if ((num == randomcont) && (App->player->vides > 0)) //SpawnShit
	{
		App->particles->randmoX = (rand() % 395 + 30);
		App->particles->randmoY = (rand() % 285 + 120);
		App->particles->randomSpawn = (rand() % 2);
		if(App->particles->randomSpawn == 0)
		App->particles->AddParticle(App->particles->Gold, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::obejcts);
		else if(App->particles->randomSpawn == 1)
		App->particles->AddParticle(App->particles->Silver, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::obejcts);
		num = 0;
		randomcont = (rand() % 500 + 10);

	}

	if (sceneTimer % 150 == 0) {
		randomEnemySpawn = (rand() % 10);
		
		switch (randomEnemySpawn) {
		case 9:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
		case 8:
		case 7:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 200);
		case 6:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
		case 5:
		case 4:
		case 3:
		case 2:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 300);
		case 1:
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 200);
		case 0:
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 200);
			break;
		}
	}


	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL); //SPRITE del fons, podem posar els altres amb (bgTexture, -512*mapaActual, 0, NULL)

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	// L10: TODO 5: Remove all memory leaks

	return true;
}