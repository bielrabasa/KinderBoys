#include "Lose.h"

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

SceneLose::SceneLose(bool startEnabled) : Module(startEnabled)
{

}

SceneLose::~SceneLose()
{

}

// Load assets
bool SceneLose::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Lose.png");
	App->audio->PlayMusic("Assets/Music/", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	App->player->CleanUp();
	App->collisions->CleanUp();
	App->particles->CleanUp();
	App->enemies->CleanUp();

	App->enemies->Disable();

	return ret;
}

UpdateResult SceneLose::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLose::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}