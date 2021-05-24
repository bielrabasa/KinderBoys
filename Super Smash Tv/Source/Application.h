#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneUPC;
class SceneIntroGame;
class SceneLevel1;
class SceneLevel2;
class SceneWin;
class SceneSwap;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleRender;

class Application
{
public:

	// Constructor. Creates all necessary modules for the application
	Application();

	// Destructor. Removes all module objects
	~Application();

	// Initializes all modules
	bool Init();

	// Updates all modules (PreUpdate, Update and PostUpdate)
	UpdateResult Update();

	// Releases all the application data
	bool CleanUp();

public:

	// Array to store the pointers for the different modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleTextures* texturesG = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneUPC* sceneUPC = nullptr;
	SceneIntroGame* sceneIntroGame = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel2* sceneLevel2 = nullptr;
	SceneWin* sceneWin = nullptr;
	SceneSwap* sceneSwap = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;

	ModuleRender* render = nullptr;

	bool pause = false;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__