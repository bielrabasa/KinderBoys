#ifndef __SCENEUPC_H__
#define __SCENEUPC_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneUPC : public Module
{
public:
	// Constructor
	SceneUPC(bool startEnabled);

	// Destructor
	~SceneUPC();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
};

#endif	// __SceneUPC_H__
