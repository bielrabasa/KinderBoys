#ifndef __SCENESWAP_H__
#define __SCENESWAP_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneSwap : public Module
{
public:
	// Constructor
	SceneSwap(bool startEnabled);

	// Destructor
	~SceneSwap();

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

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* portaTexture = nullptr;
	SDL_Texture* porta2Texture = nullptr;

	uint Win = 0;

	Animation rightAnim;
	Animation* currentAnimation;
	Animation topRightAnim;
	Animation* currentTopAnimation;

	int xplayer = 440;
	int yplayer = 225;

	int mapaTransicio = 0;
	int portaTransicio = 0;
	int Transicio = 0; //contador que va fent la transició

};

#endif	// __SCENESWAP_H__