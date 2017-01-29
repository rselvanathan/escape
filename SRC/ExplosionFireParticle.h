/*
Create A Explosion Fire Particle Effect

Author : Romesh Selvanathan
*/ 
#ifndef __EXPLOSIONFIREPARTICLE_H__
#define __EXPLOSIONFIREPARTICLE_H__

#include "ParticleEngine.h"

class ExplosionFireParticle : public ParticleEngine
{
public:
	/* Constructor */
	ExplosionFireParticle(int ttl, CVector3 position, int MaxParticles);
	/* Destructor */
	virtual ~ExplosionFireParticle();

	/* Setup the particle Effect */
	void SetupParticles();
	/* Update the Particle Effect */
	virtual void Update(float dt);
private:
};

#endif