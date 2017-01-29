/*
Create A Explosion Smoke Particle Effect

Author : Romesh Selvanathan
*/ 

#ifndef __EXPLOSIONSMOKEPARTICLE_H__
#define __EXPLOSIONSMOKEPARTICLE_H__

#include "ParticleEngine.h"

class ExplosionSmokeParticle : public ParticleEngine
{
public:
	/* Constructor */
	ExplosionSmokeParticle(int ttl, CVector3 position, int MaxParticles);
	/* Destructor */
	virtual ~ExplosionSmokeParticle();

	/* Setup the particle Effect */
	void SetupParticles();
	/* Update the Particle Effect */
	virtual void Update(float dt);
private:
};

#endif