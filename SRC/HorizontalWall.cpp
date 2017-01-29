/*
This class sets up a horizontal wall ( on the x axis)

Author : Romesh Selvanathan
*/ 
#include "HorizontalWall.h"
#include "GameObject.h"
#include "BoundingBox.h"
#include "PreLoader.h"
#include "GLBox.h"
#include "GLTexture.h"

/* Constructor */ 
HorizontalWall::HorizontalWall(CVector3 position) : GameObject("horizontalWall", NULL)
{
	// Set the current position to the position specified as a parameter
	mPosition = position;
	// Determines where the boudning box will be present. This is done as mPosition is a point in space and does not
	// represent the length and width of the bounding box. So in order to obtain that I specify the position then
	// take away from a specific vector to obtain the minimum and add to position to obtain maximum vectors which 
	// will both together surround the wall.
	mBoundingBox = new BoundingBox(this, mPosition - CVector3( 20, 30, 320), mPosition + CVector3(20, 50, 320));

	// Set the 3D opengl box up
	box.Init(5, 50, 300);
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
	box.SetTexture(PreLoader::GetInstance()->wall->texture[0]);
}

/* Destructor */ 
HorizontalWall::~HorizontalWall()
{GameObject::~GameObject();}


/* Render The object */
void HorizontalWall::Render()
{
	// render the box
	box.Render();
}