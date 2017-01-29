#include "RainParticle.h"
#include "ParticleEngine.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "PreLoader.h"
#include "GameWorld.h"

RainParticle::RainParticle(CVector3 position, int MaxParticles) 
	: ParticleEngine(0, position, MaxParticles)
{
}

RainParticle::~RainParticle()
{ParticleEngine::~ParticleEngine();}

void RainParticle::SetupParticles()
{
	xspeed = 0.0f;														// speed on the x axis
	yspeed = 0.0f;		// speed on the y axis
	scale = 1;
	texture = PreLoader::GetInstance()->particle->texture[0];

	for(ParticleList::iterator it = particles.begin(); it != particles.end(); it++)
	{
		(*it)->active=true;
		(*it)->life=1.0f;
		(*it)->fade=float(rand()%100)/1000.0f+0.003f;;			// Random Fade Speed
		(*it)->r= 1.0f;	
		(*it)->g= 0.5f;	
		(*it)->b= 0.0f;
		(*it)->mPosition.x = (*it)->mPosition.y = (*it)->mPosition.z = 0.0f;		// Center in x y z axis
		(*it)->mVelocity.x = xspeed+float((rand()%60)-32.0f) * 0.5;	// Random velocity on x axis
		(*it)->mVelocity.y = yspeed+float((rand()%60)-30.0f) * 0.5;	// Random velocity on y axis
		(*it)->mVelocity.z = float((rand()%60)-30.0f) *0.5;	// Random velocity on z axis
		(*it)->mAcceleration.x = 0.0f;							// Horizontal accelration
		(*it)->mAcceleration.y = -0.8f;						// Vertical acceleration
		(*it)->mAcceleration.z = 0.0f;							// Acceleration towrds viewer  
	}
}

void RainParticle::Update(float dt)
{
	for(ParticleList::iterator it = particles.begin(); it != particles.end(); it++)
	{
			(*it)->mPosition.x += (*it)->mVelocity.x *dt/20;	// Change in Position 
			(*it)->mPosition.y += (*it)->mVelocity.y *dt/ 20;
			(*it)->mPosition.z += (*it)->mVelocity.z *dt/20;

			(*it)->mVelocity.x += (*it)->mAcceleration.x	;				// Change in Velocity
			(*it)->mVelocity.y += (*it)->mAcceleration.y;
			(*it)->mVelocity.z += (*it)->mAcceleration.z;

			(*it)->life-=(*it)->fade;										// Reduce Particles Life By 'Fade'

			if ((*it)->life<0.0f)													// If Particle Is Burned Out
			{ 
				(*it)->life=1.0f;													// Give It New Life
				(*it)->fade=float(rand()%100)/1000.0f+0.003f;						// Random Fade Value
				(*it)->mPosition.x = (*it)->mPosition.y = (*it)->mPosition.z = 0.0f;	// Back to center
				(*it)->mVelocity.x = xspeed+float((rand()%60)-32.0f);				// Random Velocity values
				(*it)->mVelocity.y = yspeed+float((rand()%60)-30.0f);
				(*it)->mVelocity.z = float((rand()%60)-30.0f);
			}
	}
}

