/* 
Reference : nehe.gamedev.net tutorial 19
			http://nehe.gamedev.net/tutorial/lessons_16__20/28002/
Reference : Billboarding http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat
*/ 

/* 
A Base class that will be used to create different particle effects - It is a type of game object as it
will be added to the game world just like any other object. The Particle Effect Engine just creates a lot
of Particles that all have their own velocity and acceleration to create different Effects. 

This Particle Engine uses the Billboarding effect to accomplish the effect appearing in the 3D world.
Billboarding is the specidal effect used to make sure that 2D object always face the viewer at all times.
For now I am using the most simple solution to this problem , bu will change the billboarding effect solution
to a more complex one later on.

The Particle Engine is made out of a triangle Strip which together create a quad. So this means that a texture
is put on the triangle strip to create the particle effect. I am also using blending to allow the particle effect
to blend with its background and environment, which just makes sure that the edges of the textures are not shown

Author : Romesh Selvanathan
*/
#ifndef __PARTICLEENGINE_H__
#define __PARTICLEENGINE_H__

#include "GameUtil.h"
#include "Particle.h"
#include "GameObject.h"

class ParticleEngine : public GameObject
{
public:
	/* Constructor */
	ParticleEngine(int ttl, CVector3 position, int MaxParticles);
	/* Destructor */
	virtual ~ParticleEngine();

	/* Initialise Particles */
	bool Init();
	/* Setup Each Particle */
	virtual void SetupParticles() = 0;
	
	//////////////////////////////////////GameWorld Inherited Methods ////////////////////////////////////
	virtual void UpdateGravity(float dt) {/* Do not update gravity on this */}
	virtual void Update(float dt) {/* Do not apply any of the physics */}
	virtual void Render();
	//Has to be here due to inheriting Entity
	virtual void OnCollision(Entity* o){}
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create the Billboarding Effect
	void BillboardPoint();

protected:
	typedef list < SmartPtr<Particle> > ParticleList;
	ParticleList particles;						// List of particles
		
	float xspeed;								// speed in the x direction
	float yspeed;								// speed in the y direction
	float scale;								// scale of the particle effect
	int m_maxParticles;							// maximum number of particles
	unsigned int texture;						// the texture to be used by the particle effect
	int m_timeToLive;							// time to live for the particles
};

#endif