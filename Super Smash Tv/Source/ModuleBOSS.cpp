#include "ModuleBOSS.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ModuleBOSS::ModuleBOSS(bool startEnabled) : Module(startEnabled)
{
	IdleHead.Empty();
	IdleHead.PushBack({ 32, 0, 32, 32 });
	IdleHead.PushBack({ 32, 32, 32, 32 });
	IdleHead.loop = true;
	IdleHead.speed = 3;

	RHead.Empty();
	RHead.PushBack({ 64, 0, 32, 32 });
	RHead.PushBack({ 64, 32, 32, 32 });
	RHead.loop = true;
	RHead.speed = 3;

	LHead.Empty();
	LHead.PushBack({ 0, 0, 32, 32 });
	LHead.PushBack({ 0, 32, 32, 32 });
	LHead.loop = true;
	LHead.speed = 3;

	Body.Empty();
	Body.PushBack({ 0, 64, 128, 64 });
	Body.PushBack({ 128, 64, 128, 64 });
	Body.PushBack({ 0, 128, 128, 64 });
	Body.PushBack({ 128, 128, 128, 64 });
	Body.loop = true;
	Body.speed = 3;

	Wheels.Empty();
	Wheels.PushBack({ 0, 192, 64, 96 });
	Wheels.PushBack({ 64, 192, 64, 96 });
	Wheels.PushBack({ 128, 192, 64, 96 });
	Wheels.loop = true;
	Wheels.speed = 3;

	HeadAnimation = &IdleHead;
	BodyAnimation = &Body;
	WheelsAnimation = &Wheels;

	//Pit Trencat	{ 128, 0, 64, 64 }
	//Pit Trencat2	{ 196, 0, 64, 64 }

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