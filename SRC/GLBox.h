/*
A Wrapper class that represents a box done in OpenGL. This class can be called by any object that will use a box 
as its geometry. 

Author : Romesh Selvanathan
*/ 
#ifndef __GLBOX_H__
#define __GLBOX_H__

#include "GLTexture.h"

class GLBox
{
public:
	/* Constructor */
	GLBox();

	/* Destructor */
	~GLBox();

	/* Initialise the width height and length of the box */
	void Init(float Width, float Height, float Length);
	/* Set The texture to be used by this box */ 
	void SetTexture(unsigned int Texture);
	/* Set the Position of this box */
	void SetPosition(float X, float Y, float Z);
	/* Set the Color of this box, including the alpha channel */
	void SetColor(float _r, float _g, float _b, float _a);
	/* Set the yaw, pitch , roll (y, x, z) rotations of this box */
	void SetRotation(float Yaw, float Pitch, float Roll);
	/* Set the scale of this box */
	void SetScale(float Scale);
	/* Render the box */
	void Render();
private:
	float width, height, length;			// Width, Height and Length of the box
	float x, y, z;							// x, y, z positions of the box
	float r, g, b, a;						// the 3 Color components and the alpha value of the box
	float yaw, pitch, roll;					// yaw pitch and roll values of the box (for rotations)
	float scale;							// scale of the box
	unsigned int texture;					// the texture to be used by the box
};

#endif 