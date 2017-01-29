/*
Create A Spark Fire Particle Effect

Author : Romesh Selvanathan
*/ 

#include "ExplosionParticle.h"
#include "ParticleEngine.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "PreLoader.h"
#include "GameWorld.h"

/* Constructor */
ExplosionParticle::ExplosionParticle(int ttl, CVector3 position, int MaxParticles) 
	: ParticleEngine(ttl, position, MaxParticles)
{
}

/* Destructor */
ExplosionParticle::~ExplosionParticle()
{ParticleEngine::~ParticleEngine();}

/* Setup the particle Effect */
void ExplosionParticle::SetupParticles()
{
	xspeed = 0.0f;		// speed on the x axis
	yspeed = 0.0f;		// speed on the y axis
	scale = 1;			// default scale
	texture = PreLoader::GetInstance()->particle->texture[0];	// Set the texture

	// GO thorugh each particle and initialise the values
	for(ParticleList::iterator it = particles.begin(); it != particles.end(); it++)
	{
		(*it)->active=true;		// particle should be active
		(*it)->life=1.0f;		// alpha value of particle
		(*it)->fade=float(rand()%100)/1000.0f+0.003f;;	// initial random fade value(life -= fade)	
		(*it)->r= 1.0f;	// the red component of particle
		(*it)->g= 0.5f;	// the green component of particle
		(*it)->b= 0.0f; // the blue component of particle
		(*it)->mPosition.x = (*it)->mPosition.y = (*it)->mPosition.z = 0.0f; // Set the position as the center	
		// Speeding Particles up by * 10
		(*it)->mVelocity.x = xspeed+float((rand()%60)-32.0f) * 10;	// Random Valocity values
		(*it)->mVelocity.y = yspeed+float((rand()%60)-30.0f) * 10;	
		(*it)->mVelocity.z = float((rand()%60)-30.0f) * 10;	
		(*it)->mAcceleration.x = 0.0f;	// Acceleration towards certan direction (minmal downwards acceleration)						
		(*it)->mAcceleration.y = -0.2f;						
		(*it)->mAcceleration.z = 0.0f;							
	}
}

/* Update the Particle Effect */
void ExplosionParticle::Update(float dt)
{
	// GO thorugh each particle 
	for(ParticleList::iterator it = particles.begin(); it != particles.end(); it++)
	{
		// if particle is active 
		if ((*it)->active)
		{
			(*it)->mPosition.x += (*it)->mVelocity.x * dt / 15;	// Change in Position 
			(*it)->mPosition.y += (*it)->mVelocity.y * dt / 15;
			(*it)->mPosition.z += (*it)->mVelocity.z * dt / 15;

			(*it)->mVelocity.x += (*it)->mAcceleration.x * dt;	// Change in Velocity
			(*it)->mVelocity.y += (*it)->mAcceleration.y * dt;
			(*it)->mVelocity.z += (*it)->mAcceleration.z * dt;
				
			(*it)->life-=(*it)->fade;							// Reduce Particles Life By 'Fade'
		}
	}

	// Decrease its time to live and when = 0 remove it from the game world
	m_timeToLive -= 100 * dt;
	if(m_timeToLive <= 0)
		m_timeToLive = 0;
	if(m_timeToLive <= 0)
		mWorld->RemoveGameObject(this);
}

