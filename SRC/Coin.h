/*
This coin is there for the player to pick up points troughtout the game world. All this does is increase the score value
for the player

Author : Romesh Selvanathan
*/ 
#ifndef __COIN_H__
#define __COIN_H__

#include "GameObject.h"
#include "GLBox.h"

class Coin : public GameObject
{
public:
	/* Constructor */
	Coin();
	/* Destructor */ 
	virtual ~Coin();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void UpdateGravity(float dt) {/* Dont update Gravity */}
	virtual void Update(float dt);
	virtual void Render();
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	GLBox box;			// A 3D openGl box
};

#endif