#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/SpritesSSTV/Entity_Projectiles_and_gift.png");
	//textureGold = App->textures->Load("Assets/SpritesSSTV/Entity_Objects.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laserL.anim.PushBack({ 0, 11, 8, 3 }); //animació del laser Left	  //Collider Arreglat
	laserL.speed.x = 5;
	laserL.speed.y = 5;
	laserL.lifetime = 180;
	laserL.anim.speed = 0.2f;

	laserR.anim.PushBack({ 16, 11, 8, 3 }); //animació del laser Right    //Collider Arreglat
	laserR.speed.x = 5;
	laserR.speed.y = 5;
	laserR.lifetime = 180;
	laserR.anim.speed = 0.2f;

	laserU.anim.PushBack({ 10, 1, 4, 8 }); //animació del laser Up		  //Collider Arreglat
	laserU.speed.x = 5;
	laserU.speed.y = 5;
	laserU.lifetime = 180;
	laserU.anim.speed = 0.2f;

	laserD.anim.PushBack({ 10, 16, 3, 8 }); //animació del laser Down	  //Collider Arreglat	
	laserD.speed.x = 5;
	laserD.speed.y = 5;
	laserD.lifetime = 180;
	laserD.anim.speed = 0.2f;

	laserDR.anim.PushBack({ 16, 16, 6, 6 }); //animació del laser Down & Right     //Collider Arreglat
	laserDR.speed.x = 5;
	laserDR.speed.y = 5;
	laserDR.lifetime = 180;
	laserDR.anim.speed = 0.2f;
	

	laserDL.anim.PushBack({ 0, 17, 9, 5 }); //animació del laser Down & Left  //Collider Arreglat *apaño
	laserDL.speed.x = 5;
	laserDL.speed.y = 5;
	laserDL.lifetime = 180;
	laserDL.anim.speed = 0.2f;	
	
	laserUL.anim.PushBack({ 0, 0, 6, 6 }); //animació del laser Up & Left     //Collider Arreglat
	laserUL.speed.x = 5;
	laserUL.speed.y = 5;
	laserUL.lifetime = 180;
	laserUL.anim.speed = 0.2f;

	laserUR.anim.PushBack({ 16, 0, 8, 11 }); //animació del laser Up & Right	//Collider Arreglat *apaño
	laserUR.speed.x = 5;
	laserUR.speed.y = 5;
	laserUR.lifetime = 180;
	laserUR.anim.speed = 0.2f;


	Gold.anim.PushBack({ 0, 40, 16, 16 }); 
	Silver.anim.PushBack({ 16, 40, 16, 16 }); 

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	if(c2->type == c2->ENEMY && c1->type == c1->PLAYER_SHOT)
	{
		App->player->score += 3;
	}

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			// L6: DONE 6: Every time a particle hits a wall it triggers an explosion particle
			AddParticle(explosion, particles[i]->position.x, particles[i]->position.y,0);

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

UpdateResult ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}
	

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			//App->render->DrawTexture(textureGold, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y,int dir, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x+9;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y+6;
			p->direction = dir;
		
			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE) {
				//collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(),20,20);
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			}

			particles[i] = p;
			break;
		}
	}
}