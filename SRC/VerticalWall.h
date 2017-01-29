/*
This class sets up a vertical wall ( on the y axis)

Author : Romesh Selvanathan
*/ 

#ifndef __VERTICALWALL_H__
#define __VERTICALWALL_H__

#include "GameObject.h"
#include "GLBox.h"

class VerticalWall : public GameObject
{
public :
	/* Constructor */
	VerticalWall(CVector3 position);
	/* Destructor */ 
	virtual ~VerticalWall();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void Render();
	virtual bool CollisionPlaneTest(Entity* o){return false;}
	virtual void OnCollision(Entity* o){}
	////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	GLBox box;		// A 3D openGl box
};

#endif