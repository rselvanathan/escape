/*
This class represents a bullet that can be shot by either a player or enemy. This class uses 
a sphere offered by the glu library

Author : Romesh Selvanathan
*/ 

#include "Shoot.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "GameWorld.h"
#include "BoundingSphere.h"
#include "ExplosionSmokeParticle.h"
#include "ExplosionParticle.h"

/* Constructor */
Shoot::Shoot(const char* mType , CVector3 position, CVector3 velocity, int TimeToLive) : GameObject(mType, position, velocity,
	CVector3(0, 0, 0), 1, NULL), mTimeToLive(TimeToLive)
{
	// Initialise glu shape 
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GL_SMOOTH);
	gluQuadricDrawStyle(quadratic, GLU_FILL);

	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 2);
	// Set the ground value to 20
	mGroundValue = 20.0f;
} 

/* Update the Object */ 
void Shoot::Update(float dt)
{
	// If the bullet hits the ground value turn its velocity in the opposite direction
	if(mPosition.y < mGroundValue)
		mVelocity.y = mVelocity.y * -1;

	// Parent Class Update
	GameObject::Update(dt);

	// tick down the time to live value
	mTimeToLive--;
	// limit the value to 0
	if(mTimeToLive < 0 ) {mTimeToLive = 0;}
	// if it is 0 then remove the object from the game world
	if(mTimeToLive == 0)
		if(mWorld) mWorld->RemoveGameObject(this);
}

/* Render The object */ 
void Shoot::Render()
{
	// Parent class render
	GameObject::Render();
	// Render a glusphere 
	gluSphere(quadratic, 0.5, 15, 15);
}

/* Test Collisions to see if it has collided */ 
bool Shoot::CollisionTest(Entity* o)
{
	if (o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2"))
		return mBoundingSphere->CollisionTest(o->GetBoundingShape()); 
	if (o->GetType() == GameObjectType("verticalWall") || o->GetType() == GameObjectType("horizontalWall"))
		return mBoundingSphere->CollisionBoxTest(o->GetBoundingBox());
	return false;
}

/* If a Collision does occur then 
Reference for bounxing off walls : http://www.videotutorialsrock.com/opengl_tutorial/collision_detection/text.php
*/
void Shoot::OnCollision(Entity* o)
{
	if(o->GetType() == GameObjectType("verticalWall")){
	// If current position is less entity's bounding box max vector
		if(mPosition.z <= o->GetBoundingBox().GetPtr()->GetMax().z){
			// and if its below the actual entitys position.z 
			if(mPosition.z <= o->GetPosition().z){
				// make the bullet bounce off the wall
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(0, 0, -1);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
			// make the bullet bounce off the wall in the other direction
			else{
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(0, 0, 1);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
		}
	}

	if(o->GetType() == GameObjectType("horizontalWall")){
		if(mPosition.x <= o->GetBoundingBox().GetPtr()->GetMax().x){
			// and if its below the actual entitys position.z 
			if(mPosition.x <= o->GetPosition().x){
				// make the bullet bounce off the wall in the other direction
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(-1, 0, 0);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
			// make the bullet bounce off the wall in the other direction
			else{
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(1, 0, 0);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
		}
	}

	// If the object hits any of these object then make it bounce of them
	if (o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2"))
	{
		m_Bounce = true;
	}

	// Whatver collision occurs create a sprking particle effect
	ExplosionParticle* sparkParticle = new ExplosionParticle(50, mPosition, 50);
	sparkParticle->SetupParticles();
	mWorld->AddGameObject(sparkParticle);  
}
