#include "SceneSwap.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

SceneSwap::SceneSwap(bool startEnabled) : Module(startEnabled)
{

}

SceneSwap::~SceneSwap()
{

}

// Load assets
bool SceneSwap::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/EditSpritesSSTV.png");

	Transicio = 0;

	App->player->CleanUp();
	App->collisions->CleanUp();
	App->particles->CleanUp();
	App->enemies->CleanUp();

	App->enemies->Disable();
	
	return ret;
}

UpdateResult SceneSwap::Update()
{
	/*if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 0);
	}*/

	if (Transicio < 512)
		Transicio += 4;

	if(Transicio >= 512)App->fade->FadeToBlack(this, (Module*)App->sceneLevel2, 10);
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneSwap::PostUpdate()
{
	// Draw everything
	SDL_Rect fons1 = { (512*mapaTransicio) + Transicio, 0, 512, 448 }; //512*primerMapaActual, 0, 512, 448
	App->render->DrawTexture(bgTexture, 0, 0, &fons1);

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneSwap::CleanUp() {

	LOG("Freeing swap");

	//desinicialitzar tots els sprites
	App->textures->Unload(bgTexture);

	return true;
}