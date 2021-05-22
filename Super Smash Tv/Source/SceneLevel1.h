#ifndef __SCENELEVEL1_H__
#define __SCENELEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	// Constructor
	SceneLevel1(bool startEnabled);

	// Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;
	bool CleanUp() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	// Disables the player and the enemies

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* exitTexture = nullptr;

	int mapaActual = 2;
	int randomcont = 50;
	int num = 0;
	int sceneTimer = 0; //3601 si vols veure el final directe, 0 per default.
	int randomEnemySpawn = 0;
	short portesSpawn[4][9][2];
	int i = 0;
	int exitTimer = 0;
};

#endif  // __SCENELEVEL1_H__