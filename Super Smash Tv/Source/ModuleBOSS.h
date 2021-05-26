#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleBOSS : public Module
{
public:
	// Constructor
	ModuleBOSS(bool startEnabled);

	// Destructor
	~ModuleBOSS();

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

	Animation IdleHead;
	Animation RHead;
	Animation LHead;
	Animation Body;
	Animation Wheels;

	Animation* HeadAnimation = nullptr;
	Animation* BodyAnimation = nullptr;
	Animation* WheelsAnimation = nullptr;

	Collider* collider = nullptr;

	int x = 208; //Wheels centered (horizontal)
	int y = -64; //Wheels out of the map (top)

	int bossTimer = 0;

};

#endif	// __ModuleBOSS_H__