#include "SceneUPC.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneUPC::SceneUPC(bool startEnabled) : Module(startEnabled)
{

}

SceneUPC::~SceneUPC()
{

}

// Load assets
bool SceneUPC::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Pantalla_uni.png");
	//bgTexture = App->textures->Load("Assets/SpritesSSTV/Pantalla_Kinderboys.png");
	App->audio->PlayMusic("Assets/Music/", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

bool SceneUPC::CleanUp() {
	App->textures->Unload(bgTexture);
	return true;
}

UpdateResult SceneUPC::Update()
{
	GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || pad.a == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntroGame, 20);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneUPC::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}