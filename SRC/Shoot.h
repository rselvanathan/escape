/*
This class represents a bullet that can be shot by either a player or enemy. This class uses 
a sphere offered by the glu library

Author : Romesh Selvanathan
*/ 

#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "GameObject.h"

class Shoot : public GameObject
{
public:
	/* Constructor */
	Shoot(const char* mType, CVector3 position, CVector3 velocity, int TimeToLive);
	/* Destructor */ 
	virtual ~Shoot() {GameObject::~GameObject();}

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void UpdateGravity(float dt){/* Dont apply gravity to this */ };
	virtual void Update(float dt);
	virtual void Render();
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Set Time to Live and Obtain the time to live for the buller */ 
	void SetTimeToLive(int t){mTimeToLive = t;}
	int GetTimeToLive(){return mTimeToLive;}

private:
	GLUquadricObj* quadratic;	// quadratic used to init a glu quadratic used to draw a glu sphere
	int mTimeToLive;			// the time to live till this object is removed from the game world
};

#endif