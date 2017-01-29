/*
Child class of BoundingShape. This class is the bounding sphere that will test its collision with other Bounding Shapes.
Bounding Sphere is a very fast and easy way to determine if two objects have collided as an object is surrounded by
a Sphere. That sphere has a radius which is equal in all directions, so no need to worry about object rotations. This means
that if the distance between the two object positions is less than the two radiuses of the bounding sphere added together 
then a collision has occured.

This class also presents Collision detection with a Bounding box and (Alpha stage) Plane collision

Author : Romesh Selvanathan

Reference : Chris Child , 2nd Year Asteroids Project
*/ 
#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "GameUtil.h"
#include "GameObjectType.h"
#include "BoundingShape.h"
#include "BoundingBox.h"

class BoundingSphere : public BoundingShape
{
public:
	// Constructor 
	BoundingSphere() : BoundingShape("BoundingSphere"), mRadius(0) 
	{	// Init glu Quadratic's to be used to visually draw the bounding sphere (Debugging)
		quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GL_SMOOTH);
		gluQuadricDrawStyle(quadratic, GLU_LINE);
	}

	BoundingSphere(SmartPtr<Entity> o, float r) : BoundingShape("BoundingSphere", o), mRadius(r) 
	{	// Init glu Quadratic's to be used to visually draw the bounding sphere (Debugging)
		quadratic= gluNewQuadric();
		gluQuadricNormals(quadratic, GL_SMOOTH);
		gluQuadricDrawStyle(quadratic, GLU_LINE);
	}
	// Method to test if the collision between two spheres is occuring 
	bool CollisionTest(SmartPtr<BoundingSphere> bs) {
		// Check if the two collision shapes are sphere
		if (GetType() == bs->GetType()) {
			// obtain the collision sphere
			BoundingSphere* bsphere = (BoundingSphere*) bs.GetPtr();
			// obtain the two position 
			CVector3 pos1 = GetEntity()->GetPosition();
			CVector3 pos2 = bsphere->GetEntity()->GetPosition();
			// work out the distance between them
			float distance = (pos2 - pos1).Length();
			// work out the collision distance by adding both collision spheres radiuses together
			float collision_distance = GetRadius() + bsphere->GetRadius();
			// return whether the distance is less than the collision distance
			return (distance <= collision_distance);
		}
		return false;
	}

	/*
	Obtains the Current Entity's position as well as the min and max value from the bounding box.
	max - min = length, width and height of the bounding box. This Test Basically checks if the 
	current position of the entity is inside the box. If it is then a
	collision has occured.
	*/
	bool CollisionBoxTest(SmartPtr<BoundingBox> bx){
		CVector3 pos = GetEntity()->GetPosition();
		CVector3 b_min = bx->GetMin();
		CVector3 b_max = bx->GetMax();
		return pos.x <= b_max.x && pos.x >= b_min.x &&
			   pos.y <= b_max.y && pos.y >= b_min.y &&
			   pos.z <= b_max.z && pos.z >= b_min.z;
	}
	/* 
	Collision Test to see if this Sphere is colliding with a given Plane. The equation is:
	Distance = DOT(plane.normal, sphere.position) - d (d From Plane equation, which is worked out as 
														d = DOT(plane.vertex , plane.normal)
	So if the distance from the plane is less than the radius than a collision has occured 
	(NOT FINAL - a few bugs)
	This can be used as world boundaries as a plane is infinite in length making sure a player does not go beyond a bound 
	*/
	bool CollisionPlaneTest(CVector3 normal, float d)
	{
		CVector3 position = GetEntity()->GetPosition();
		float distance = (position.Dot(normal)) - d;
		if(abs(distance) < mRadius)
			return true;
		return false;
	}

	// Draw the sphere for debugging 
	/*void Render()
	{
		glPushMatrix();
			glTranslatef(GetEntity()->GetPosition().x, GetEntity()->GetPosition().y, GetEntity()->GetPosition().z);
			gluSphere(quadratic, mRadius, 15, 15);
		glPopMatrix();
	}*/

	// Get and Set Methods
	void SetRadius(float r) { mRadius = r; }
	float GetRadius() { return mRadius; }

protected:
	float mRadius;				// Radius of Sphere
	GLUquadricObj* quadratic;	// quadratic used to init a glu quadratic used to draw a glu sphere (Debugging) 
};

#endif