/*
An Entity Base class for any class that is going to be part of the game world itself. All classes in the game world
will be linked to this class. This is for Collision Detection purposes mainly.

Author : Romesh Selvanathan
*/
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "GLVector.h"
#include "GameObjectType.h"

class BoundingSphere;
class BoundingBox;
class GameWorld;

class Entity 
{
public:
	/* Constructors */ 
	Entity(char const * const type_name) : mType(type_name), mPosition(0, 0, 0),
		mVelocity(0, 0, 0), mAcceleration(0, 0, 0), mScale(1), mAlive(true){}
	Entity(char const * const type_name, CVector3 pos, CVector3 vel, CVector3 acc,float scale,bool isAlive) : 
					mType(type_name), mPosition(pos), mVelocity(vel), mAcceleration(acc),
						mScale(scale), mAlive(isAlive) {}
	/* Destructor */ 
	virtual ~Entity(){}

	/* Initialise method */
	virtual bool Init() = 0;
	/* Clean up method */
	virtual bool CleanUp(){return false;}

	/* Testing and Resloving Collisions */
	virtual bool CollisionTest(Entity* o) { return false; }
	virtual bool CollisionPlaneTest(Entity* o) {return false;}
	virtual void OnCollision(Entity* o) = 0;

	/* Get Methods */
	const SmartPtr<BoundingSphere> GetBoundingShape() const { return mBoundingSphere; }
	const SmartPtr<BoundingBox> GetBoundingBox() const { return mBoundingBox;}
	const CVector3 GetPosition() const {return mPosition;}
	const CVector3 GetVelocity() const {return mVelocity;}
	const CVector3 GetAcceleration() const {return mAcceleration;}
	const bool IsAlive() const {return mAlive;}
	const GameObjectType& GetType() const { return mType; }
	const float GetScale() const{return mScale;}
	const GameWorld* GetWorld(){return mWorld;}

	/* Set Methods */
	void SetPosition(CVector3 v){mPosition = v;}
	void SetVelocity(CVector3 v){mVelocity = v;}
	void SetAcceleration(CVector3 v){mAcceleration = v;}
	void SetAlive(bool v) {mAlive = v;}
	void SetScale(float v){mScale = v;}
	void SetGameWorld(GameWorld* world){mWorld = world;}

protected:
	GameObjectType mType;						// Type of Game Entity

	bool mAlive;								// Is the Entity Alive?
	CVector3 mPosition;							// The Current position of the entity
	CVector3 mVelocity;							// The Velocity of the entity
	CVector3 mAcceleration;						// The Acceleration of the Entity
	float mScale;								// The scale of the entity

	SmartPtr<BoundingSphere> mBoundingSphere;	// The BoundingSphere for the Entity
	SmartPtr<BoundingBox> mBoundingBox;			// The BoundingBox for the Entity
	GameWorld* mWorld;							// Pointer to the current game world of the entity
};

#endif 