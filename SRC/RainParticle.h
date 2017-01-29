#ifndef __RAINPARTICLE_H__
#define __RAINPARTICLE_H__

#include "ParticleEngine.h"

class RainParticle : public ParticleEngine
{
public:
	RainParticle( CVector3 position, int MaxParticles);
	virtual ~RainParticle();

	void SetupParticles();

	virtual void Update(float dt);
private:
};

#endif