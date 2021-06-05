#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__

#include "Module.h"
#include "Animation.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


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

	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	Animation* HeadAnimation = nullptr;
	Animation* BodyAnimation = nullptr;
	Animation* WheelsAnimation = nullptr;
	Animation* ArmAnimation = nullptr;

	Animation IdleHead;
	Animation RHead;
	Animation LHead;
	Animation Body;
	Animation Wheels;
	Animation Body2;
	Animation Body3;
	Animation RightArm;
	Animation emptyAnimation;

	Collider* collider = nullptr;

	int x = 192; //Wheels centered (horizontal), 192 està perfecte
	int y = -150; //Wheels out of the map (top), -150 està perfecte

	int torreta1x = 0;
	int torreta1y = 0;

	int torreta2x = 0;
	int torreta2y = 0;

	int xoffset = 10; //10
	int yoffset = 10; //10

	int currentvidaBOSS = 150;

	int offsetYhead = -64;

	//Usado para la rafaga de disparos del boss
	bool bandera = true;
	bool baderaShot = false;
	int cont = 0;
	int contShot = 200;
	int Shots = 0;
	int explosiontimer = 0;
	bool TimeShot = false;
	int TimeShotInt = 0;

	//Movimiento de enemigo
	int movimiento_x;
	int movimiento_y;
	int contmovx;
	int contmovy;
	int startlvl;

	int bossTimer = 0;
	uint laserFx = 0;
};

#endif	// __ModuleBOSS_H__