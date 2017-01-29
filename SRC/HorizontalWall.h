/*
This class sets up a horizontal wall ( on the x axis)

Author : Romesh Selvanathan
*/ 

#ifndef  __HORIZONTALWALL_H__
#define  __HORIZONTALWALL_H__

#include "GameObject.h"
#include "GLBox.h"

class HorizontalWall : public GameObject
{
public:
	/* Constructor */
	HorizontalWall(CVector3 position);
	/* Destructor */ 
	virtual ~HorizontalWall();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void Render();
	virtual bool CollisionPlaneTest(Entity* o){return false;}
	virtual void OnCollision(Entity* o){}
	////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	GLBox box;		// A 3D openGl box
};

#endif 