#include "SceneIntroGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"

SceneIntroGame::SceneIntroGame(bool startEnabled) : Module(startEnabled)
{

}

SceneIntroGame::~SceneIntroGame()
{

}

// Load assets
bool SceneIntroGame::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/sstv_Title.png");
	//bgTexture = App->textures->Load("Assets/SpritesSSTV/Pantalla_Kinderboys.png");
	App->audio->PlayMusic("Assets/Music/02-_Super_Smash_TV_-_Title_Screen.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

bool SceneIntroGame::CleanUp() {
	App->textures->Unload(bgTexture);
	return true;
}

UpdateResult SceneIntroGame::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || pad.a == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneSwap, 20);
		App->sceneLevel_1->levelcont = 0;
		App->player->score = 0;
		App->player->vides = 5;
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntroGame::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}