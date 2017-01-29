/*
This coin is there for the player to pick up points troughtout the game world. All this does is increase the score value
for the player

Author : Romesh Selvanathan
*/ 

#include "Coin.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingSphere.h"
#include "GameWorld.h"
#include "GLBox.h"
#include "PreLoader.h"
#include "GLTexture.h"

/* Constructor */ 
Coin::Coin() : GameObject("coin", NULL)
{
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 10);

	// Set the 3D opengl box up
	box.Init(5, 5, 1);
	// set its texture
	box.SetTexture(PreLoader::GetInstance()->score->texture[0]);
}

/* Destructor */ 
Coin::~Coin()
{
	GameObject::~GameObject();
}

/* Update the Coin */ 
void Coin::Update(float dt)
{
	// Parent class update 
	GameObject::Update(dt);
	// Rotate the object (100 is the right value to make it rotate by a certain amount)
	mYRot += 100 * dt;
	// if y rotation is greater than 360 then reset the value
	if(mYRot > 360)
		mYRot = 0;

	// Update the box position color and rotation
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
	box.SetColor(1, 1, 0, 0);
	box.SetRotation(mYRot, mXRot, mZRot);
}

/* Render The object */ 
void Coin::Render()
{
	// render the box
	box.Render();
}

/* Test Collisions to see if it has collided */ 
bool Coin::CollisionTest(Entity* o)
{
	if(o->GetType() != GameObjectType("player")) return false;
	return mBoundingSphere->CollisionTest(o->GetBoundingShape());
}

/* If collision occured then */ 
void Coin::OnCollision(Entity* o)
{
	// remove the object from the world
	mWorld->RemoveGameObject(this);
}