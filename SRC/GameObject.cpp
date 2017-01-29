/*
This class Inherits from the Entity class but is the parent class for any gameobject that can be manipulated
or changed by the player. In other words any object the player can interact with ( eg enemies, walls).
This class will apply basic physics to those objects aswel and simplfy the update and Render functions for those
objects.

Author : Romesh Selvanathan
*/
#include "GameUtil.h"
#include "GameObject.h"
#include "GameObjectType.h"
#include "Entity.h"
#include "Graphics.h"

/* Constructors */
GameObject::GameObject(char const * const type_name, SmartPtr<Model_3DS> model) 
													: Entity(type_name),
													p_Model(model),
													mYRot(0.0f),
													mXRot(0.0f),
													mZRot(0.0f),
													r(1), g(1), b(1),
													mGroundValue(20.f),
													m_ApplyFriction(false),
													m_Bounce(false)
{
}

GameObject::GameObject(char const * const type_name, CVector3 position,CVector3 velocity,CVector3 acceleration,float 
		scale,SmartPtr<Model_3DS> model) : Entity(type_name, position, velocity,acceleration,scale, true),
										   p_Model(model),
										   r(1), g(1), b(1),
										   mGroundValue(20.f),
										   m_ApplyFriction(false),
										   m_Bounce(false)
											
{
} 

/* Destructor */
GameObject::~GameObject()
{
	SAFE_DELETE(p_Model);
	Entity::~Entity();
}

// Implements Gravity To the Object
void GameObject::UpdateGravity(float dt)
{
	// if 3Ds model is not null then update its position 
	if(p_Model.GetPtr() != NULL){
		p_Model->pos.x = mPosition.x;
		p_Model->pos.y = mPosition.y;
		p_Model->pos.z = mPosition.z;
	}
	// A Safety check to see if object is below specified ground level
	if(mPosition.y <= mGroundValue){
		// If true then set the position to ground level
		mPosition.y = mGroundValue;
		// Set the Up Velocity in y to 0 so that it stops the object from making funny movements.
		mVelocity.y = 0;
	}
	
	// IF it is not Integrate the Position and Velocity with gravity until it does reach ground level
	if(mPosition.y > mGroundValue){
		// GRAVITY_DIRECTION represents the vector of gravity which is downwards. Upwards being (0, 1, 0) so 
		// downwards would be (0, -1, 0). So the direction gravity gives a vector which will accelerate
		// objects towards the "ground"
		mVelocity = mVelocity + ((GRAVITY_DIRECTION * GRAVITY) *dt);
		mPosition.y = mPosition.y + (mVelocity.y *dt);
	}
}

void GameObject::Update(float dt)
{
	// if 3Ds model is not null then update its position, rotatioan etc 
	if(p_Model.GetPtr() != NULL){
		p_Model->rot.y =  mYRot;

		p_Model->pos.x = mPosition.x;
		p_Model->pos.y = mPosition.y;
		p_Model->pos.z = mPosition.z;

		p_Model->color.x = r;
		p_Model->color.y = g;
		p_Model->color.z = b;

		p_Model->scale = mScale;
	}

	// If friction can be applied to this object 
	if(m_ApplyFriction) {
		// This checks if the velocity is greater than 0 in x and z if yes 
		if(abs(mVelocity.x) > 0 && abs(mVelocity.z) > 0){
			// calculate friction which is the opposite on the Velocity (so Velocity * -1 for opposite direction)
			// then multiply by a coefficient of fricition in this case 0.95 (value between 0 and 1)
			CVector3 friction = (mVelocity.Normalize() * -1) * 0.95;
			// adding it onto acceleration as I am turning each object into mass = 1
			// F = ma is F = 1 x a then f = a, which means friction is "a" so add this acceleration to friction
			mAcceleration.x = mAcceleration.x + friction.x;
			mAcceleration.z = mAcceleration.z + friction.z;
		}
		// This value decays the Velocity in x and z gradually to 0 combined with the friction
		// This 0.92 value can be changed to anything and the the higher (higher in 0.0"v" value) it is the more the object will move before stopping
		mVelocity.x = mVelocity.x * 0.92;
		mVelocity.z = mVelocity.z * 0.92; 
	}

	if(m_Bounce){
		// Sets the Velocity and Accelertation in the opposite direction so that objects
		// bounce of each other
		mVelocity = mVelocity * -1;
		mAcceleration = mAcceleration * -1;
		m_Bounce = false;
	}

	// Integrate the Velocity (v = u + at)
	mVelocity = mVelocity + (mAcceleration * dt);
	// Integrate the Position
	mPosition = mPosition + (mVelocity * dt);
}

/* Render The Object */
void GameObject::PreRender()
{
	Graphics::GetInstance()->StoreMatrix();
}

void GameObject::Render()
{
	if(p_Model.GetPtr() != NULL){
		p_Model->Draw();
	}
	// Stil being used by bullets so need to change that
	else{
		Graphics::GetInstance()->Translate(mPosition.x, mPosition.y, mPosition.z);
		Graphics::GetInstance()->Color3(r, g, b);
		Graphics::GetInstance()->Scale(mScale);
	} 
}

void GameObject::PostRender()
{
	Graphics::GetInstance()->ReleaseMatrix();
}