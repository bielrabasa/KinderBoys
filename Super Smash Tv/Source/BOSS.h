#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BOSS : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BOSS(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;
	Animation UpAnim;
	Animation DownAnim;
	Animation LeftAnim;
	Animation RightAnim;
	Animation ULAnim;
	Animation URAnim;
	Animation DRAnim;
	Animation DLAnim;

	int movementDirections = 0;


	// Delay entre els moviments de l'enemic
	int movementDelay = 0;
	int spawntimer = 0;
};

#endif // __ENEMY_BROWNSHIP_H__