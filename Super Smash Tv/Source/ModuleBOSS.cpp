#include "ModuleBOSS.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ModuleBOSS::ModuleBOSS(bool startEnabled) : Module(startEnabled)
{

}

ModuleBOSS::~ModuleBOSS()
{

}

// Load assets
bool ModuleBOSS::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Entity_BOSS.png");

	//CARREGAR ANIMACIONS

	return ret;
}

bool ModuleBOSS::CleanUp() {
	App->textures->Unload(bgTexture);
	return true;
}

UpdateResult ModuleBOSS::Update()
{
	
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleBOSS::PostUpdate()
{

	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}