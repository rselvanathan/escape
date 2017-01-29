/*
A child class of the BoundingShape class which represent a Bounding Box. It is a Axis Aligned Bounding box not object Aligned.
A bounding box is a very fast type of collision check just like the sphere however it does not fit well for complex objects
such as meshes. This class has two Vector values which represent the minimum and maximum. maximum - minimum = length, width height
of the box. The Check for the Collision detection is presented in BoundingSphere class with this class.

Author : Romesh Selvanathan
*/ 
#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include "BoundingShape.h"
#include "GameUtil.h"

class BoundingBox : BoundingShape
{
public:
	/* Constructors */ 
	BoundingBox() : BoundingShape("BoundingBox")
	{
		min = max = CVector3(0, 0, 0);
	}
	BoundingBox(SmartPtr<Entity> o, CVector3 _min, CVector3 _max) : BoundingShape("BoundingBox", o)
	{
		min = _min; max = _max;
	}

	/* Set And Get MIN, MAX Vectors */ 
	void SetMinMax(CVector3 _min, CVector3 _max) {min = _min; max = _max;}
	CVector3 GetMin() {return min;}
	CVector3 GetMax() {return max;}

	/* Debugging */ 
	/*void Render()
	{
		glPushMatrix();

		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
			glVertex3f(max.x, max.y, min.z);
			glVertex3f(min.x, max.y, min.z);
			glVertex3f(min.x, min.y, min.z);
			glVertex3f(max.x, min.y, min.z);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(max.x, min.y, max.z);
			glVertex3f(max.x, max.y, max.z);
			glVertex3f(min.x, max.y, max.z);
			glVertex3f(min.x, min.y, max.z);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(max.x, max.y, min.z);
			glVertex3f(max.x, max.y, max.z);
			glVertex3f(min.x, max.y, max.z);
			glVertex3f(min.x, max.y, min.z);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(max.x, min.y, max.z);
			glVertex3f(min.x, min.y, max.z);
			glVertex3f(min.x, min.y, min.z);
			glVertex3f(max.x, min.y, min.z);
		glEnd();

		glPopMatrix();
	}*/
private:
	CVector3 min, max;			// Min, Max Vectors for the box
};

#endif 