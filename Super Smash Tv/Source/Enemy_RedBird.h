#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_RedBird : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_RedBird(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;
	// Delay entre els moviments de l'enemic
	int movementDelay = 0;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	int spawntimer = 0;


	

	// The enemy animation
	Animation flyAnim;
	Animation UpAnim;
	Animation DownAnim;
	Animation LeftAnim;
	Animation RightAnim;
	Animation ULAnim;
	Animation URAnim;
	Animation DRAnim;
	Animation DLAnim;

	int movementDirections = 0;

};

#endif // __ENEMY_REDBIRD_H__