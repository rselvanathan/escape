/*
These Portals allow th eplayer to move from one part of the world to another. There are currently
2 portals one that moves from the first part of the world to the second and another which allows
the player to complete the game

Author : Romesh Selvanathan
*/ 

#include "Portal.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingSphere.h"
#include "PreLoader.h"
#include "GameObjectType.h"

/* Constructor */
Portal::Portal(const char* name) : GameObject(name, NULL)//"Square")
{
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 30);

	// Set up the 3D model
	p_Model = new Model_3DS();
	p_Model->Load("door.3ds");
	SetModel(p_Model);

	// Initialise values
	red = blue = red2 = blue2 = yellow2 = false;
}

/* Destructor */ 
Portal::~Portal()
{GameObject::~GameObject();}

/* Test Collisions to see if it has collided */
bool Portal::CollisionTest(Entity* o)
{
		if(o->GetType() != GameObjectType("player")) return false;
		return mBoundingSphere->CollisionTest(o->GetBoundingShape());
}

/* If Collision does occur then */
void Portal::OnCollision(Entity* o)
{
	// If it is the first portal and the switches are turned on then fire message to listeners
	if(GetType() == GameObjectType("portal") && blue && red) {
		FireOnPortalEntered(1);
	}
	// If it is the second portal and the switches are turned on then fire message to listeners
	if(GetType() == GameObjectType("portal2") && blue2 && red2 && yellow2) {
		FireOnPortalEntered(2);
	}
}

////////////////////////////////////////////ISWITCHLISTENER/////////////////////////////////////////
void Portal::OnSwitchTurned(bool _blue, bool _red)
{
	// If it is false then set the switches to true
	if(!red)
		red = _red;
	if(!blue)
		blue = _blue;
}

void Portal::OnSwitchTurned2(bool _blue, bool _red, bool _yellow)
{
	// If it is false then set the switches to true
	if(!red2)
		red2 = _red;
	if(!blue2)
		blue2 = _blue;
	if(!yellow2)
		yellow2 = _yellow;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////