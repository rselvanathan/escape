/*
There are two types of powerups the player can obtain currently. These are the energy powerup and health powerup
and as their names suggest their increase either the energy or health values back up again

Author : Romesh Selvanathan
*/ 
#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "GameObject.h"
#include "GLBox.h"

class PowerUp : public GameObject
{
public:
	/* Constructor */
	PowerUp(const char* name);
	/* Destructor */ 
	virtual ~PowerUp();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void UpdateGravity(float dt) {/* Dont update Gravity */}
	virtual void Update(float dt);
	virtual void Render();
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	GLBox box;		// A 3D openGl box
};

#endif