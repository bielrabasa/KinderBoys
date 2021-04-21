#include "Particle.h"

#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
										frameCount(p.frameCount), lifetime(p.lifetime)
{

}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen

		switch (direction) {
		case 0:
			break;
		case 1://amunt
			position.y -= speed.y;
			break;

		case 2://Esq
			position.x -= speed.x;
			break;

		case 3://drt
			position.x += speed.x;
			break;

		case 4://avall
			position.y += speed.y;
			break;

		case 5://Esq, amunt
			position.y -= speed.y;
			position.x -= speed.x;
			break;

		case 6://drt, amunt
			position.y -= speed.y;
			position.x += speed.x;
			break;

		case 7://Esq, avall
			position.y += speed.y;
			position.x -= speed.x;
			break;

		case 8://drt, avall
			position.y += speed.y;
			position.x += speed.x;
			break;
		}
		/*position.x += speed.x;
		position.y += speed.y;*/

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}