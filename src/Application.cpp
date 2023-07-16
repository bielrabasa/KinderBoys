#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneUPC.h"
#include "SceneIntroGame.h"
#include "SceneLevel1.h"
#include "level2.h"
#include "SceneWin.h"
#include "SceneSwap.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleBOSS.h"

Application::Application()
{
	modules[0]  = new ModuleWindow     (true);
	modules[1]  = new ModuleInput      (true);
	modules[2]  = new ModuleTextures   (true);
	modules[3]  = new ModuleAudio      (true);
	modules[4]  = new SceneIntro       (true);
	modules[5]  = new SceneUPC         (false);
	modules[6]  = new SceneIntroGame   (false);
	modules[7]  = new SceneLevel1      (false);
	modules[8]  = new SceneLevel2      (false);
	modules[9]  = new SceneWin         (false);
	modules[10] = new SceneSwap        (false);
	modules[11] = new ModuleEnemies    (false);
	modules[12] = new ModulePlayer     (false);
	modules[13] = new ModuleBOSS       (false);
	modules[14] = new ModuleParticles  (false);
	modules[15] = new ModuleCollisions (true);
	modules[16] = new ModuleFadeToBlack(true);
	modules[17] = new ModuleRender     (true);
	
	//L'ORDRE D'SPRITES NO ÉS CORRECTE (Original)
	//modules[6] =	player =		new ModulePlayer(false);	//Player starts disabled
	//modules[7] =	particles =		new ModuleParticles(true);
	//modules[8] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled
	//PLAYER HA D'ESTAR PER SOBRE DE ENEMIES (pels sprites de portes), i PARTICLES (ha d'estar necessariament per sobre dels 2, sinó dona problemes)
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

	if (!pause)
	{
		for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
			ret = modules[i]->IsEnabled() ? modules[i]->Update() : UpdateResult::UPDATE_CONTINUE;
	}

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
