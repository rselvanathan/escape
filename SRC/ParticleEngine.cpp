/* 
Reference : nehe.gamedev.net tutorial 19
			http://nehe.gamedev.net/tutorial/lessons_16__20/28002/
Reference : Billboarding http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat

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


#include "ParticleEngine.h"
#include "Particle.h"
#include "GameUtil.h"
#include "PreLoader.h"
#include "GLTexture.h"
#include "GameWorld.h"

/* Constructor */
ParticleEngine::ParticleEngine(int ttl, CVector3 position, int MaxParticles) : GameObject("ParticleEngine", NULL),
	m_timeToLive(ttl),
	m_maxParticles(MaxParticles),
	scale(1)
{
	mPosition = position;
	Init();
}

/* Destructor */
ParticleEngine::~ParticleEngine()
{
	GameObject::~GameObject();
}

/* Initialise Particle Engine */ 
bool ParticleEngine::Init()
{
	// Create each particle and add them to the list
	for(int loop=0;loop < m_maxParticles; loop++) {
		SmartPtr<Particle> particle = new Particle();
		particles.push_back(particle);
	}
	return true;
}

/* Render the Particle Effect */
void ParticleEngine::Render()
{
	// Allow Blending and Enable Texture 2D
	BLEND_TEX_ON;
	// Bind a Texture to the particle effect
	glBindTexture(GL_TEXTURE_2D, texture);
	// Move the Particle Effect to a certain position
	glTranslatef(mPosition.x,mPosition.y,mPosition.z);
	// Loop throught each particl effect
	for(ParticleList::iterator it = particles.begin(); it != particles.end(); it++)
	{
		// if the particle is active
		if ((*it)->active)
		{
			// Store the Current Matrix
			glPushMatrix();
			// Billboard the Particle Effect
			BillboardPoint();
			// Scale each Particle
			glScalef(scale, scale, scale);
			// Apply the Color to each Particle
			glColor4f((*it)->r,(*it)->g,(*it)->b,(*it)->life);
			// Begin Drawing the Triangle Strip
			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				glTexCoord2d(1,1); glVertex3f((*it)->mPosition.x+0.5f,			// Top Right
											  (*it)->mPosition.y+0.5f,
											  (*it)->mPosition.z);
				glTexCoord2d(0,1); glVertex3f((*it)->mPosition.x-0.5f,			// Top Left
											  (*it)->mPosition.y+0.5f,
											  (*it)->mPosition.z);
				glTexCoord2d(1,0); glVertex3f((*it)->mPosition.x+0.5f,			// Bottom Right
											  (*it)->mPosition.y-0.5f,
											  (*it)->mPosition.z);
				glTexCoord2d(0,0); glVertex3f((*it)->mPosition.x-0.5f,			// Bottom Left
											  (*it)->mPosition.y-0.5f,
											  (*it)->mPosition.z);
			glEnd();
			// Reset back to previous matrix
			glPopMatrix();
		}
	}// Done Building Triangle Strip

	// Disable Blending and Texture 2D
	BLEND_TEX_OFF;
}

// Create the Billboarding Effect
// code from : http://www.lighthouse3d.com/opengl/billboarding/index.php3?billCheat
void ParticleEngine::BillboardPoint()
{
	// An array to hold the 4x4 matrix (4x4 = 16) of model view
	float modelview[16];
	// two temp values
	int i,j;

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);

	// This resets all the scaling and rotations
	for( i=0; i<3; i++ ) 
	    for( j=0; j<3; j++ ) {
		if ( i==j )
		    modelview[i*4+j] = 1.0;
		else
		    modelview[i*4+j] = 0.0;
	    }

	// set the modelview with no rotations and scaling
	glLoadMatrixf(modelview);
}

