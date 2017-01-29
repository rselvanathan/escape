/*
A Square that is used to switch on the switches ( Mainly used to show some phsycis stuff ) 

Author : Romesh Selvanathan
*/ 

#ifndef __TESTSQUARE_H__
#define __TESTSQUARE_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "GLBox.h"

class TestSquare : public GameObject
{
public :
	/* Constructor */
	TestSquare(const char* name);
	/* Destructor */
	virtual ~TestSquare();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void Update(float dt);
	virtual void Render();
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	GLBox box;		// A 3D openGl box
};

#endif