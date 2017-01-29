/*
This is wrapper class around OpenGL which wraps the most frequently and most common Opengl API calls.
This means that if I do choose to switch to DirectX for example all I have to do is change these methods 
without changing the whole game by a Lot.

This class will be global singleton class as I do not want to allow object to contain this. Neither do I want
to create pointers of this class as it will cause more errors. Moreover it will also increase in memory
where most classes will use this to access the OpenGL commands. So keeping it a global singleton where only
one of this object ever exists and any class can access it is the best way to come around that problem.

Author : Romesh Selavanthan
*/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "GameUtil.h"

class Graphics
{
public:
	/* Initialise the Singleton */
	static Graphics* GetInstance(){
		if(mInstance == NULL)
			mInstance = new Graphics();
		return mInstance;
	}

	/* Clears The Screen (Depth Buffer and Color) */
	void ClearScreen();

	/* Set up a Orthographic View */
	void SetOrthoView(int left, int right, int top, int bottom);
	/* Set up a Perspective View */
	void SetPerspective();

	/* Store the Current Matrix in the stack */
	void StoreMatrix(){glPushMatrix();}
	/* Reset the Last matrix, by popping current matrix from the Stack */
	void ReleaseMatrix(){glPopMatrix();}
	/* Reset the matrix by Loading in the Identity Matrix */
	void ResetMatrix(){glLoadIdentity();}

	/* Translate Call */
	void Translate(float x, float y, float z){glTranslatef(x, y, z);}
	/* Rotate in X axis */
	void RotateX(float angle){glRotatef(angle, 1, 0, 0);}
	/* Rotate in Y axis */
	void RotateY(float angle){glRotatef(angle, 0, 1, 0);}
	/* Rotate in Z axis */
	void RotateZ(float angle){glRotatef(angle, 0, 0, 1);}
	/* Set Color */
	void Color3(float r, float g, float b) {glColor3f(r, g, b);}
	/* Set Color including the alpha channel */
	void Color4(float r, float g, float b, float a){glColor4f(r, g, b, a);}
	/* Scale an object , if you wish in an uneven way */
	void Scale(float x, float y, float z){glScalef(x, y, z);}
	/* Scale an object where all sides are scaled in same way*/
	void Scale(float scale){glScalef(scale, scale, scale);}

	/* Bind A 2D Texture */
	void Bind2DTexture(unsigned int texture) {glBindTexture(GL_TEXTURE_2D, texture);}

	/* Draw a simple Quad - only used by one class for now */
	void DrawQuad(float width, float height, float length);
	/* Draw a 2D Quad */
	void Draw2DQuad(float minX, float maxX, float minY, float maxY, 
		float texMinX, float texMaxX, float texMinY, float texMaxY);

private:
	Graphics(){}
	static Graphics* mInstance;
};

#endif