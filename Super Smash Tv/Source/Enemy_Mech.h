#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Mech(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation TurretDown;
	Animation TurretDownR;
	Animation TurretDownL;
	Animation TurretUp;
	Animation TurretUpR;
	Animation TurretUpL;
	Animation TurretLeft;
	Animation TurretLeftD1;
	Animation TurretLeftD2;
	Animation TurretLeftU1;
	Animation TurretLeftU2;
	Animation TurretRight;
	Animation TurretRightD1;
	Animation TurretRightD2;
	Animation TurretRightU1;
	Animation TurretRightU2;

	int shootdelay = 5;
	int rafagadelay = 25;
	int contdispar = 0;

};

#endif // __ENEMY_MECH_H__