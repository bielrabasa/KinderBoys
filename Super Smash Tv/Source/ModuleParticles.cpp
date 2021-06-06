#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "moduleaudio.h"
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
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	LOG("Loading particles");
	texture = App->textures->Load("Assets/SpritesSSTV/Entity_Projectiles_and_gift.png");
	//textureGold = App->textures->Load("Assets/SpritesSSTV/Entity_Objects.png");

	// Explosion particle
	explosion.anim.Empty();
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laserL.anim.Empty();
	laserL.anim.PushBack({ 0, 11, 8, 3 }); //animació del laser Left	  //Collider Arreglat
	laserL.speed.x = 15;
	laserL.speed.y = 15;
	laserL.lifetime = 180;
	laserL.anim.speed = 0.2f;

	laserR.anim.Empty();
	laserR.anim.PushBack({ 16, 11, 8, 3 }); //animació del laser Right    //Collider Arreglat
	laserR.speed.x = 15;
	laserR.speed.y = 15;
	laserR.lifetime = 180;
	laserR.anim.speed = 0.2f;

	laserU.anim.Empty();
	laserU.anim.PushBack({ 10, 1, 4, 8 }); //animació del laser Up		  //Collider Arreglat
	laserU.speed.x = 15;
	laserU.speed.y = 15;
	laserU.lifetime = 180;
	laserU.anim.speed = 0.2f;

	laserD.anim.Empty();
	laserD.anim.PushBack({ 10, 16, 3, 8 }); //animació del laser Down	  //Collider Arreglat	
	laserD.speed.x = 15;
	laserD.speed.y = 15;
	laserD.lifetime = 180;
	laserD.anim.speed = 0.2f;

	laserDR.anim.Empty();
	laserDR.anim.PushBack({ 16, 16, 6, 6 }); //animació del laser Down & Right     //Collider Arreglat
	laserDR.speed.x = 15;
	laserDR.speed.y = 15;
	laserDR.lifetime = 180;
	laserDR.anim.speed = 0.2f;
	
	laserDL.anim.Empty();
	laserDL.anim.PushBack({ 0, 17, 9, 5 }); //animació del laser Down & Left  //Collider Arreglat *apaño
	laserDL.speed.x = 15;
	laserDL.speed.y = 15;
	laserDL.lifetime = 180;
	laserDL.anim.speed = 0.2f;	
	
	laserDL.anim.Empty();
	laserUL.anim.PushBack({ 0, 0, 6, 6 }); //animació del laser Up & Left     //Collider Arreglat
	laserUL.speed.x = 15;
	laserUL.speed.y = 15;
	laserUL.lifetime = 180;
	laserUL.anim.speed = 0.2f;

	laserUR.anim.Empty();
	laserUR.anim.PushBack({ 16, 0, 8, 11 }); //animació del laser Up & Right	//Collider Arreglat *apaño
	laserUR.speed.x = 15;
	laserUR.speed.y = 15;
	laserUR.lifetime = 180;
	laserUR.anim.speed = 0.2f;

	//BossShot
	laserBossL.anim.Empty();
	laserBossL.anim.PushBack({ 34, 105, 15, 13 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossL.speed.x = 5;
	laserBossL.speed.y = 5;
	laserBossL.lifetime = 40;
	laserBossL.anim.speed = 0.2f;

	laserBossLD1.anim.Empty();
	laserBossLD1.anim.PushBack({ 49, 105, 17, 15 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossLD1.speed.x = 5;
	laserBossLD1.speed.y = 5;
	laserBossLD1.lifetime = 40;
	laserBossLD1.anim.speed = 0.2f;

	laserBossLD2.anim.Empty();
	laserBossLD2.anim.PushBack({ 49, 105, 17, 15 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossLD2.speed.x = 5;
	laserBossLD2.speed.y = 5;
	laserBossLD2.lifetime = 40;
	laserBossLD2.anim.speed = 0.2f;

	laserBossLD3.anim.Empty();
	laserBossLD3.anim.PushBack({ 67, 105, 14, 14 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossLD3.speed.x = 5;
	laserBossLD3.speed.y = 5;
	laserBossLD3.lifetime = 40;
	laserBossLD3.anim.speed = 0.2f;

	laserBossR.anim.Empty();
	laserBossR.anim.PushBack({ 49, 25, 15, 13 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossR.speed.x = 5;
	laserBossR.speed.y = 5;
	laserBossR.lifetime = 40;
	laserBossR.anim.speed = 0.2f;

	laserBossRD1.anim.Empty();
	laserBossRD1.anim.PushBack({ 32, 25, 17, 15 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossRD1.speed.x = 5;
	laserBossRD1.speed.y = 5;
	laserBossRD1.lifetime = 40;
	laserBossRD1.anim.speed = 0.2f;

	laserBossRD2.anim.Empty();
	laserBossRD2.anim.PushBack({ 32, 25, 17, 15 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossRD2.speed.x = 5;
	laserBossRD2.speed.y = 5;
	laserBossRD2.lifetime = 40;
	laserBossRD2.anim.speed = 0.2f;

	laserBossRD3.anim.Empty();
	laserBossRD3.anim.PushBack({ 17, 25, 14, 14 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossRD3.speed.x = 5;
	laserBossRD3.speed.y = 5;
	laserBossRD3.lifetime = 40;
	laserBossRD3.anim.speed = 0.2f;

	laserBossD.anim.Empty();
	laserBossD.anim.PushBack({ 0, 11, 8, 3 }); //animació del laser Left	  //Collider Arreglat  //Es te que cambiar el sprite per el del BossShot
	laserBossD.speed.x = 5;
	laserBossD.speed.y = 5;
	laserBossD.lifetime = 40;
	laserBossD.anim.speed = 0.2f;

	//BossShotExplosion
	laserBossLEx.anim.Empty();
	laserBossLEx.anim.PushBack({ 64, 24, 15, 15 }); //animació del laser Left	  //Collider Arreglat  //Es te que ficar el sprite de la explosio de la enemicshot
	laserBossLEx.speed.x = 0;
	laserBossLEx.speed.y = 0;
	laserBossLEx.lifetime = 70;
	laserBossLEx.anim.speed = 0.2f;

	TripleShoot.anim.Empty();	//animació del Triple Shoot	//Collider Arreglat *apaño
	TripleShoot1.anim.Empty();	//animació del Triple Shoot	//Collider Arreglat *apaño
	TripleShoot2.anim.Empty();	//animació del Triple Shoot	//Collider Arreglat *apaño
	TripleShoot.anim.PushBack({56, 8, 7, 7});
	TripleShoot1.anim.PushBack({56, 8, 7, 7});
	TripleShoot2.anim.PushBack({56, 8, 7, 7});
	//TripleShoot.speed.x = 15;
	//TripleShoot.speed.y = 15;
	TripleShoot.lifetime = 180;
	TripleShoot1.lifetime = 180;
	TripleShoot2.lifetime = 180;
	TripleShoot.anim.speed = 0.2f;
	TripleShoot1.anim.speed = 0.2f;
	TripleShoot2.anim.speed = 0.2f;

	Gold.anim.Empty();
	Gold.anim.PushBack({ 500, 500, 17, 17 });
	Gold.anim.PushBack({ 0, 40, 17, 17 });
	Gold.anim.loop = false;
	Gold.lifetime = 666;
	laserUR.anim.speed = 0.1f;

	Silver.anim.Empty();
	Silver.anim.PushBack({ 16, 40, 16, 16 }); 
	Silver.lifetime = 666;

	SilverGold.anim.Empty();
	SilverGold.anim.PushBack({ 32, 40, 16, 16 });
	SilverGold.lifetime = 666;

	Cash.anim.Empty();
	Cash.anim.PushBack({ 48, 40, 16, 16 });
	Cash.lifetime = 666;

	blood.anim.Empty();
	blood.anim.PushBack({ 102, 0, 16, 16 }); 
	blood.anim.PushBack({ 118, 0, 16, 16 }); 
	blood.anim.PushBack({ 134, 0, 16, 16 }); 
	blood.anim.PushBack({ 102, 16, 16, 16 }); 
	blood.anim.PushBack({ 118, 16, 16, 16 }); 
	blood.anim.PushBack({ 134, 16, 16, 16 }); 
	//blood.lifetime = 10;
	blood.anim.speed = 0.175f;
	blood.anim.loop = false;

	Triple.anim.Empty();
	Triple.anim.PushBack({33, 72, 15, 15});
	Triple.lifetime = 666;

	vidaUp.anim.Empty();
	vidaUp.anim.PushBack({17, 104, 15, 15});
	vidaUp.lifetime = 666;

	ShootdeathT.anim.Empty();
	ShootdeathT.anim.PushBack({0, 33, 7, 7});
	ShootdeathT.lifetime = 10;

	Torreta.anim.Empty();
	Torreta.anim.PushBack({64, 17, 7, 7});
	Torreta.lifetime = 150;

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

	//desinicialitzar sprites
	App->textures->Unload(texture);


	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == c2->ENEMY && c1->type == c1->PLAYER_SHOT 
		|| c2->type == c2->Door && c1->type == c1->PLAYER_SHOT 
		|| c2->type == c2->WALL && c1->type == c1->PLAYER_SHOT)
	{
		
		App->audio->PlayFx(explosionFx);
	}

	if (c2->type == c2->ENEMY && c1->type == c1->PLAYER_SHOT)
	{
	App->player->score += 30;
	}

	if (c2->type == c2->ENEMY && c1->type == c1->PLAYER_TRIPLE_SHOT)
	{
	App->player->score += 30;
	}


	//particules quan la bala colisiona contra la pared
	/*if (c2->type == c2->WALL && c1->type == c1->PLAYER_SHOT)
	{
		App->particles->AddParticle(App->particles->ShootdeathT, App->player->position.x, App->particles->laserU.position.y, 6, Collider::Type::WALL);
	}*/

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

	if (Gold.lifetime <= 300)
	{
		Gold.anim.loop = true;
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
			App->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()), 1.5f);
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