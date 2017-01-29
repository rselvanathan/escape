/*
A Square that is used to switch on the switches ( Mainly used to show some phsycis stuff ) 

Author : Romesh Selvanathan
*/ 

#include "TestSquare.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "BoundingSphere.h"
#include "PreLoader.h"
#include "GLTexture.h"

/* Constructor */ 
TestSquare::TestSquare(const char* name) : GameObject(name, NULL)//"Square")
{
	// Set the Bounding Sphere up
	mBoundingSphere = new BoundingSphere(this, 16);

	// Set the 3D opengl box up
	box.Init(15, 15, 15);
	box.SetTexture(PreLoader::GetInstance()->crate->texture[0]);

	// Apply friction to this object
	m_ApplyFriction = true;
	// Set the Ground level for this object (For gravity)
	mGroundValue = 16;
}

/* Destructor */ 
TestSquare::~TestSquare()
{GameObject::~GameObject();}

/* Update the Object */ 
void TestSquare::Update(float dt)
{
	// Parent class update
	GameObject::Update(dt);
	// Update the box position, color
	box.SetPosition(mPosition.x, mPosition.y, mPosition.z);
	box.SetColor(r, g, b, 1);
}

/* Render The object */ 
void TestSquare::Render()
{
	// render the box
	box.Render();
}

/* Test Collisions to see if it has collided */ 
bool TestSquare::CollisionTest(Entity* o)
{
	if (o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2") || o->GetType() == GameObjectType("enemy"))
		return mBoundingSphere->CollisionTest(o->GetBoundingShape()); 
	if (o->GetType() == GameObjectType("verticalWall") || o->GetType() == GameObjectType("horizontalWall"))
		return mBoundingSphere->CollisionBoxTest(o->GetBoundingBox());
	return false;
}

/* If a Collision does occur then 
Reference for bounxing off walls : http://www.videotutorialsrock.com/opengl_tutorial/collision_detection/text.php
*/
void TestSquare::OnCollision(Entity* o)
{
	// If collision with the front wall 
	if(o->GetType() == GameObjectType("verticalWall")){
		// If current position is less entity's bounding box max vector
		if(mPosition.z <= o->GetBoundingBox().GetPtr()->GetMax().z){
			// and if its below the actual entitys position.z 
			if(mPosition.z <= o->GetPosition().z){
				// make the box bounce off the wall
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(0, 0, -1);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
				
			}
			// make the box bounce off the wall in the other direction
			else{
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(0, 0, 1);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
		}
	}

	if(o->GetType() == GameObjectType("horizontalWall")){
		if(mPosition.x <= o->GetBoundingBox().GetPtr()->GetMax().x){
			// and if its below the actual entitys position.z 
			if(mPosition.x <= o->GetPosition().x){
				// make the box bounce off the wall in the other direction
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(-1, 0, 0);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
			// make the box bounce off the wall in the other direction
			else{
				// Preset the normal for this side of the wall
				CVector3 normal = CVector3(1, 0, 0);
				// Obtain current acceleration of the box
				CVector3 a = mAcceleration;
				// obtain the new acceleration which will be current A - (2*new directional acceleration)
				a = a - CVector3(normal * 2 * a.Dot(normal));
				mAcceleration = a;	

				// Same has to be done with velocity so that the slowing down the direction travelled is consistent
				CVector3 v = mVelocity;
				v = v - CVector3(normal * 2 * v.Dot(normal));
				mVelocity = v;	
			}
		}
	}

	// If collision occurs with these objects then make the box bounce off them
	if (o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2") || o->GetType() == GameObjectType("enemy"))
	{
		m_Bounce = true;
	}
}