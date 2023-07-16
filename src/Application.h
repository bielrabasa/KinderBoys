#pragma once
#include <array>
#include "Globals.h"

#define NUM_MODULES 18

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
class ModuleBOSS;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	UpdateResult Update();
	bool CleanUp();

	union {
		std::array<Module*, NUM_MODULES> modules;
		struct {
			ModuleWindow*      window;
			ModuleInput*       input;
			ModuleTextures*    textures;
			ModuleAudio*       audio;
			SceneIntro*        sceneIntro;
			SceneUPC*          sceneUPC;
			SceneIntroGame*    sceneIntroGame;
			SceneLevel1*       sceneLevel1;
			SceneLevel2*       sceneLevel2;
			SceneWin*          sceneWin;
			SceneSwap*         sceneSwap;
			ModuleEnemies*     enemies;
			ModulePlayer*      player;
			ModuleBOSS*        boss;
			ModuleParticles*   particles;
			ModuleCollisions*  collisions;
			ModuleFadeToBlack* fade;
			ModuleRender*      render; 
		};
	};

	bool pause = false;

};

// Global var made extern for Application ---
extern Application* App;

