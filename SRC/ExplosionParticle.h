/*
Create A Explosion Spark Particle Effect

Author : Romesh Selvanathan
*/ 
#ifndef __EXPLOSIONPARTICLE_H__
#define __EXPLOSIONPARTICLE_H__

#include "ParticleEngine.h"

class ExplosionParticle : public ParticleEngine
{
public:
	/* Constructor */
	ExplosionParticle(int ttl, CVector3 position, int MaxParticles);
	/* Destructor */
	virtual ~ExplosionParticle();

	/* Setup the particle Effect */
	void SetupParticles();
	/* Update the Particle Effect */
	virtual void Update(float dt);
private:
};

#endif