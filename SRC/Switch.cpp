/*
There are a number of switches in the game world which will have to be activated in order to enter a portal

Author : Romesh Selvanathan
*/ 

#include "Switch.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "PreLoader.h"
#include "GLTexture.h"

/* Constructor */
Switch::Switch(const char* name) : GameObject(name, NULL)
{
	// Initialise values
	blue = red = red2 = blue2 = yellow2 = false;
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 40);
	// Set the 3D opengl box up
	box.Init(30, 0.2, 30);
	box.SetTexture(PreLoader::GetInstance()->switchtex->texture[0]);
}

/* Destructor */ 
Switch::~Switch()
{GameObject::~GameObject();}

/* Update the Object */ 
void Switch::Update(float dt)
{
	//Parent class Update function
	GameObject::Update(dt);
	// Update the box position color and rotation
	box.SetColor(r, g, b, 1);
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
}

/* Render The object */
void Switch::Render()
{
	// render the box
	box.Render();
}

/* Test Collisions to see if it has collided */ 
bool Switch::CollisionTest(Entity* o)
{
	if(o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") || o->GetType() == GameObjectType("bluesquare2") ||
		o->GetType() == GameObjectType("yellowsquare2"))
		return mBoundingSphere->CollisionTest(o->GetBoundingShape());
	return false;
}

/* If a Collision does occur then */
void Switch::OnCollision(Entity* o)
{
	// If the color of the switch matches the colliding square's color then 
	// send the appropriate message to all its listeners
	if(mType == GameObjectType("blueswitch") && o->GetType() == GameObjectType("bluesquare")) {
		blue = true;
		FireSwitchTurned();
	}
	if(mType == GameObjectType("redswitch") && o->GetType() == GameObjectType("redsquare")) {
		red = true;
		FireSwitchTurned();
	}
	if(mType == GameObjectType("redswitch2") && o->GetType() == GameObjectType("redsquare2")) {
		red2 = true;
		FireSwitch2Turned();
	}
	if(mType == GameObjectType("blueswitch2") && o->GetType() == GameObjectType("bluesquare2")) {
		blue2 = true;
		FireSwitch2Turned();
	}
	if(mType == GameObjectType("yellowswitch2") && o->GetType() == GameObjectType("yellowsquare2")) {
		yellow2 = true;
		FireSwitch2Turned();
	}
}