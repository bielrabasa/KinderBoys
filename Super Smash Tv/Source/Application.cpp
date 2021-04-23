#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	sceneIntro =	new SceneIntro(true);
	modules[5] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	
	modules[6] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[7] =	particles =		new ModuleParticles(true);
	modules[8] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	
	/*
	modules[6] =	particles =		new ModuleParticles(true);
	modules[7] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	modules[8] =	player =		new ModulePlayer(false);	//Player starts disabled	*/

	modules[9] =	collisions =	new ModuleCollisions(true);
	modules[10] =	fade =			new ModuleFadeToBlack(true);

	modules[11] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		// WARNING: When deleting a pointer, set it to nullptr afterwards
		// It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

UpdateResult Application::Update()
{
	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UpdateResult::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
