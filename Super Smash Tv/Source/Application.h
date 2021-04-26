#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneUPC;
class SceneLevel1;
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
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__