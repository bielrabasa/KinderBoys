#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Pantalla_Kinderboys.png");
	App->audio->PlayMusic("Assets/Music/", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

bool SceneIntro::CleanUp() {
	App->textures->Unload(bgTexture);
	return true;
}

UpdateResult SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || pad.a == KeyState::KEY_DOWN)
	{
		//App->fade->FadeToBlack(this, (Module*)App->sceneLevel2, 20); //Comentar-Descomentar per probar la segona fase
		App->fade->FadeToBlack(this, (Module*)App->sceneUPC, 20);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntro::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}