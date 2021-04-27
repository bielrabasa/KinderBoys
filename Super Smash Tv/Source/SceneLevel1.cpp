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
	App->collisions->AddCollider({ 480, 210,16, 79 }, Collider::Type::Door);//Puerta derecha


	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);


	// Enemies ---
	/*App->enemies->AddEnemy(Enemy_Type::REDBIRD, 350, 200);
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
	*/
	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->vides = 5;
	App->player->score = 0;

	// L10: TODO 2: Enable (and properly disable) the player module
	App->player->Enable();

	srand(time(NULL));
	sceneTimer = 0;

	return ret;
}

UpdateResult SceneLevel1::Update()
{
	//App->render->camera.x += 3; //SCROLL
	++num;
	if(sceneTimer < 3601)	++sceneTimer;

	//if ((App->input->keys[SDL_SCANCODE_Q] == KeyState::KEY_REPEAT) && (App->player->vides > 0)) //SpawnShit
	if ((num == randomcont) && (App->player->vides > 0) && (sceneTimer <= 3600)) //SpawnShit
	{
		App->particles->randmoX = (rand() % 395 + 30);
		App->particles->randmoY = (rand() % 285 + 120);
		App->particles->randomSpawn = (rand() % 4);
		if(App->particles->randomSpawn == 0)
		App->particles->AddParticle(App->particles->Gold, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::object_gold);
		else if(App->particles->randomSpawn == 1)
		App->particles->AddParticle(App->particles->Silver, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::object_silver);
		else if(App->particles->randomSpawn == 2)
		App->particles->AddParticle(App->particles->Cash, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::object_money);
		else if(App->particles->randomSpawn == 3)
		App->particles->AddParticle(App->particles->SilverGold, App->particles->randmoX, App->particles->randmoY, 6, Collider::Type::object_silver_gold);
		
		num = 0;
		randomcont = (rand() % 300 + 5);
	}

	if (sceneTimer % 150 == 0 && sceneTimer <= 3600) {//3600frames, 6 rondes, 24 aparicions random
		randomEnemySpawn = (rand() % 10);
		
		
		if (i == 0) { //porta de dalt
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 105 + 195); //porta abaix X (random entre 195 i 300)
				portesSpawn[i][j][1] = (rand() % 30 - 20); //porta adalt Y
			}
		}

		if (i == 1) { //porta esquerra
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 30 - 5);
				portesSpawn[i][j][1] = (rand() % 65 + 185);
			}
		}

		if (i == 2) { //porta dreta
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 30 + 500);
				portesSpawn[i][j][1] = (rand() % 65 + 185);
			}
		}

		if (i == 3) { //porta abaix
			for (int j = 0; j < 9; ++j) {
				portesSpawn[i][j][0] = (rand() % 105 + 195); //porta abaix X (random entre 195 i 300)
				portesSpawn[i][j][1] = (rand() % 30 + 400); //porta abaix Y
			}
		}


		switch (randomEnemySpawn) {
		case 9:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][0][0], portesSpawn[i][0][1]);
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][1][0], portesSpawn[i][1][1]);
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][2][0], portesSpawn[i][2][1]);
		case 8:
		case 7:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][3][0], portesSpawn[i][3][1]);
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, portesSpawn[i][4][0], portesSpawn[i][4][1]);
		case 6:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][5][0], portesSpawn[i][5][1]);
		case 5:
		case 4:
		case 3:
		case 2:
			App->enemies->AddEnemy(Enemy_Type::REDBIRD, portesSpawn[i][6][0], portesSpawn[i][6][1]);
		case 1:
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, portesSpawn[i][7][0], portesSpawn[i][7][1]);
		case 0:
			App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, portesSpawn[i][8][0], portesSpawn[i][8][1]);
			break;
		}
		
		++i;
		if (i == 4) i = 0;
	}

	if (i == 1) mapaActual = 7;
	else mapaActual = 0;


	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, -512*mapaActual, 0, NULL); //SPRITE del fons, podem posar els altres amb (bgTexture, -512*mapaActual, 0, NULL)

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	// L10: TODO 5: Remove all memory leaks

	return true;
}