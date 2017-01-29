/*
This class sets up a vertical wall ( on the z axis)

Author : Romesh Selvanathan
*/ 
#include "VerticalWall.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "PreLoader.h"
#include "GLBox.h"

/* Constructor */ 
VerticalWall::VerticalWall(CVector3 position) : GameObject("verticalWall", NULL)//"Square")
{
	// Set the current position to the position specified as a parameter
	mPosition = position;
	// Determines where the boudning box will be present. This is done as mPosition is a point in space and does not
	// represent the length and width of the bounding box. So in order to obtain that I specify the position then
	// take away from a specific vector to obtain the minimum and add to position to pbtain maximum vectors which 
	// will both together surrownd the wall.
	mBoundingBox = new BoundingBox(this, mPosition - CVector3(200, 50, 20), mPosition + CVector3(200, 50, 20));

	// Set the 3D opengl box up
	box.Init(200, 50, 5);
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
	box.SetTexture(PreLoader::GetInstance()->wall->texture[0]);
}

/* Destructor */
VerticalWall::~VerticalWall()
{GameObject::~GameObject();}

/* Render The object */
void VerticalWall::Render()
{
	// render the box
	box.Render();
}
