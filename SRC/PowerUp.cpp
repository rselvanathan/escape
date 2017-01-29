/*
There are two types of powerups the player can obtain currently. These are the energy powerup and health powerup
and as their names suggest their increase either the energy or health values back up again

Author : Romesh Selvanathan
*/ 

#include "PowerUp.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingSphere.h"
#include "PreLoader.h"
#include "GLTexture.h"
#include "GameWorld.h"
#include "ParticleEngine.h"

/* Constructor */ 
PowerUp::PowerUp(const char* name) : GameObject(name, NULL)//"Square")
{
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 10);

	// Set the 3D opengl box up
	box.Init(7, 7, 7);

	// depending on the name given to the powerup change the texture of it
	if(name == "poweruphealth")
		box.SetTexture(PreLoader::GetInstance()->heartcrate->texture[0]);
	else if (name == "powerupenergy")
		box.SetTexture(PreLoader::GetInstance()->energycrate->texture[0]);
}

/* Destructor */ 
PowerUp::~PowerUp()
{GameObject::~GameObject();}

/* Update the object */
void PowerUp::Update(float dt)
{
	// Parent class update 
	GameObject::Update(dt);

	// Rotate the object
	// Each yaw pitch and roll have different rotation values
	mYRot += 100. * dt;
	mXRot += 51.f * dt;
	mZRot += 25.f * dt;
	// reset them when they reach 360
	if(mYRot > 360)
		mYRot = 0;
	if(mXRot > 360)
		mXRot = 0;
	if(mZRot > 360)
		mZRot = 0;

	// Update the box position color and rotation
	box.SetRotation(mYRot, mXRot, mZRot);
	box.SetColor(1,1, 1, 0);
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
}

/* Render The object */
void PowerUp::Render()
{
	// render the box
	box.Render();
}

/* Test Collisions to see if it has collided */
bool PowerUp::CollisionTest(Entity* o)
{
	if(o->GetType() != GameObjectType("player")) return false;
	return mBoundingSphere->CollisionTest(o->GetBoundingShape());
}

/* If Collision does occur then */
void PowerUp::OnCollision(Entity* o)
{
	// remove the object from the world
	mWorld->RemoveGameObject(this);
}