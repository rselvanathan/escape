/*
This class Inherits from the Entity class but is the parent class for any gameobject that can be manipulated
or changed by the player. In other words any object the player can interact with ( eg enemies, walls).
This class will apply basic physics to those objects aswel and simplfy the update and Render functions for those
objects.

Author : Romesh Selvanathan
*/

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "GLVector.h"
#include "Model_3DS.h"
#include "Entity.h"
#include "SmartPtr.h"

#define GRAVITY 9.81f							// The Acceleration of gravity
#define GRAVITY_DIRECTION CVector3(0, -1, 0)	// The direction the gravity is pulling objects towards

class GameObject : public Entity
{
public:
	/* Constructors */
	GameObject(char const * const type_name, SmartPtr<Model_3DS> model);
	GameObject(char const * const type_name,CVector3 position,CVector3 velocity,
		CVector3 acceleration,float scale,SmartPtr<Model_3DS> model);

	/* Destructor */
	virtual ~GameObject();

	/* Inherited From Entity */
	virtual bool Init(){return false;};

	/* Apply Gravity on the Object */
	virtual void UpdateGravity(float dt);
	/* Update the Object with Basic Physics as well as normal updates */
	virtual void Update(float dt);
	/* Render The Object */
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	/* If a collision occurs */
	virtual void OnCollision(GameObject* o){}

	/* Get methods */
	float GetGroundValue(){return mGroundValue;}

	/* Set Methods */
	void SetGroundValue(float v) {mGroundValue = v;}
	void SetRotation(float x , float y, float z){mXRot = x; mYRot = y; mZRot = z;}
	void SetModel(SmartPtr<Model_3DS> Model){p_Model = Model;}
	void SetColor(float R, float G, float B) {r = R; g = G; b = B;}

protected:
	float mXRot, mYRot, mZRot;				// Yaw, Pitch and Roll values
	float r, g, b;							// The 3 color values
	float mGroundValue;						// Y value of specific height object should consider ground (Different for different objects)
	SmartPtr<Model_3DS> p_Model;			// Pointer to 3Ds model			

	bool m_ApplyFriction;					// Should friction be applied to object?	
	bool m_Bounce;							// Should Object bounce off other objects ?
};

#endif