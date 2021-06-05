#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	UpdateResult PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	//Audio explosion
	uint explosionFx = 0;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y,int dir, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);


	int randmoX = 225;
	int randmoY = 200;
	int randomSpawn = 0;

	int parpa = 0;

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;


	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	//Template particle for an explosion
	Particle explosion;


	Particle Gold;
	Particle Silver;
	Particle SilverGold;
	Particle Cash;


	Particle Triple;
	Particle vidaUp;



	Particle blood;

	//Template particle for a laser
	Particle laserL;
	Particle laserR;
	Particle laserU;
	Particle laserD;
	Particle laserDR;
	Particle laserDL;
	Particle laserUL;
	Particle laserUR;

	//LaserBoss
	Particle laserBossL;
	Particle laserBossR;
	Particle laserBossLD1;
	Particle laserBossLD2;
	Particle laserBossLD3;
	Particle laserBossD;
	Particle laserBossRD1;
	Particle laserBossRD2;
	Particle laserBossRD3;

	//LaserBossExplosion
	Particle laserBossLEx;

	Particle TripleShoot;
	Particle TripleShoot1;
	Particle TripleShoot2;

	Particle ShootdeathT;
	Particle ShootdeathD;
	Particle ShootdeathL;
	Particle ShootdeathR;

	Particle Torreta;
};

#endif // __MODULEPARTICLES_H__