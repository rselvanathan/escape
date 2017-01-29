/*
This class is a wrapper class currently for the Camera Class in the engine. As this game is a first person
that means the camera is the player. However having code such as Collision detection and shooting makes the camera
class a bit bloated. So I wanted to keep the camera class seperate and just worry about the view itself rather
than the extra things. So this class handles all those things for the Camera as well as updating the camera
as necessary

Author : Romesh Selvanathan
*/ 

#include "Player.h"
#include "GameUtil.h"
#include "IEnemyListener.h"
#include "Entity.h"
#include "Camera.h"
#include "BoundingSphere.h"
#include "Shoot.h"
#include "GameWorld.h"

/* Construstor */
Player::Player(CVector3 position, CVector3 lookAt, CVector3 Up) : Entity("player", CVector3(0, 0, 0), CVector3(0, 0, 0), CVector3(0, 0, 0),1, true)
{
	// Set up the camera
	camera.Reset();
	camera.PositionCamera(position, lookAt, Up);

	// Set up the Bounding SPhere
	mBoundingSphere = new BoundingSphere(this, 15);

	// Initialise the values 
	move =  m_hasAttacked =  sprint = false;
	m_tillNextAttack = 100;
	m_speed = 0.0f;
}

/* Destructor */
Player::~Player()
{Entity::~Entity();}

/* Update this object */ 
void Player::Update(float dt)
{
	// Update the camera 
	camera.SetIsSprinting(sprint);
	camera.Update(dt);

	// Update the current position of the player ( equal to the camera position)
	// (NOTE: necessary for collision , especially with the portals as it works with the parent class Entity )
	mPosition = camera.Position();

	// if the player has been attacked recently
	if(m_hasAttacked){
		// decrease value
		m_tillNextAttack -= 100 * dt;
		// check to make sure it don't go below 0
		if(m_tillNextAttack < 0) {m_tillNextAttack = 0;}
		// if 0 reset the value and allow attacking again
		if(m_tillNextAttack==0){
			m_hasAttacked = false;
			m_tillNextAttack = 100;
		}
	}
}

/* Render this object onto the scren */
void Player::Render()
{
	// Allow the camera to look around the world with gluLookAt
	camera.Look();
}

/* Move Player */ 
void Player::MovePlayer(float speed)
{
	// if moving is not hindered
	if(!move)
		// move the camera
		camera.MoveCamera(speed);
	else
		// if it is hindered then allow movement again
		move = false;
}

/* Allow the player to strafe */ 
void Player::StrafePlayer(float speed)
{	
	// Allow the camera to strafe
	camera.StrafeCamera(speed);
}

/* Allow the player to look around */
void Player::SetViewByMouse(float x, float y)
{
	// set the camera view 
	camera.SetViewByMouse(x, y);
}

/* Shoots a Bullet at the current view direction */
void Player::ShootBullet()
{
	// obtain view from camera and position
	CVector3 view = camera.View();
	CVector3 pos = camera.Position();
	// Get the current direction the bullet should fly towards
	CVector3 direction = view - pos;
	// Obtain the normalized vector
	direction.Normalize();
	// Preset an acceleration
	float bullet_acceleration = 0.5f;
	// Determine velocity
	CVector3 velocity = direction * bullet_acceleration;
	// Create new Shoot Object with camera poisition and the velocity worked out
	Shoot* playerShoot = new Shoot("bullet", pos, velocity, 550);
	playerShoot->SetColor(0.0f, 0.0f, 1.0f);
	// Set the time on how long the bullet should be alive
	playerShoot->SetTimeToLive(100);
	// Add to the world
	mWorld->AddGameObject(playerShoot);
	mWorld->AddCollisionEntity(playerShoot);
}

//////////////////////////////////////////////IPortalListener/////////////////////////////////////////
void Player::OnPortalEnter(int portal)
{
	// If the first portal is entered then set the new position of the camera
	if(portal == 1){
		mPosition = CVector3(500, 35, 500);
		camera.SetViewVector(CVector3(-1, 1, 0));
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

/* Test Collisions to see if it has collided */ 
bool Player::CollisionTest(Entity* o) 
{ 
	if (o->GetType() == GameObjectType("verticalWall") || o->GetType() == GameObjectType("horizontalWall"))
		return mBoundingSphere->CollisionBoxTest(o->GetBoundingBox());
	else if(o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2") || o->GetType() == GameObjectType("enemybullet") ||
		o->GetType() == GameObjectType("portal") || o->GetType() == GameObjectType("portal2"))
		return mBoundingSphere->CollisionTest(o->GetBoundingShape());
	else
		return false;
}

/* If a Collision does occur then */
void Player::OnCollision(Entity* o)
{
	// Obtain current position of camera
	CVector3 pos = camera.Position();

	// If collision with the vertical wall 
	if(o->GetType() == GameObjectType("verticalWall")){
		// If current position is less entity's bounding box max vector
		if(pos.z <= o->GetBoundingBox().GetPtr()->GetMax().z){
			// and if its below the actual entitys position.z 
			if(pos.z <= o->GetPosition().z){
				// then make sure camera does not move beyond that point
				camera.SetZPosition(o->GetBoundingBox().GetPtr()->GetMin().z);
			}
			// else dont let it move beyond the max point
			else{
				camera.SetZPosition(o->GetBoundingBox().GetPtr()->GetMax().z);
			}
		}
	}
	// If collision with the horizontal wall 
	if(o->GetType() == GameObjectType("horizontalWall")){
		// If current position is less entity's bounding box max vector
		if(pos.x <= o->GetBoundingBox().GetPtr()->GetMax().x){
			// and if its below the actual entitys position.z 
			if(pos.x <= o->GetPosition().x){
				// then make sure camera does not move beyond that point
				camera.SetXPosition(o->GetBoundingBox().GetPtr()->GetMin().x);
			}
			// else dont let it move beyond the max point
			else{
				camera.SetXPosition(o->GetBoundingBox().GetPtr()->GetMax().x);
			}
		}
	} 

	// IF collision with any of the colored boxes
	if(o->GetType() == GameObjectType("redsquare") || o->GetType() == GameObjectType("bluesquare") ||
		o->GetType() == GameObjectType("redsquare2") ||  o->GetType() == GameObjectType("bluesquare2") || 
		o->GetType() == GameObjectType("yellowsquare2")){
		// Obtain the current direction the camera is facing
		CVector3 direction = camera.View() - pos;
		// Normalize the vector
		direction.Normalize();
		float acc;
		// if sprinting preset the acceleration magnitude by a higher amount
		if(!sprint)
			acc = 0.1f;
		else
			acc = 0.5f;
		// Set the new Accelerating vector
		CVector3 v = direction * acc;
		// Set the y to 0 so that is does not move up
		v.y = 0.0f;
		// Set the objects acceleration
		o->SetAcceleration(v);
		// Stop moving the camera - (So it does not move thorugh the box)
		move = true;
	}

	// if collision with a enemy bullet
	if(o->GetType() == GameObjectType("enemybullet")){
		// if player has not been attacked recently
		if(!m_hasAttacked){
			// Fire that enemy has been attacked the player
			FireEnemyAttack();
			// player has been recently attacked
			m_hasAttacked = true;
		}
	}

	// If the collision with a portal occurs
	if(o->GetType() == GameObjectType("portal") || o->GetType() == GameObjectType("portal2"))
	// then set the current x position and y position from the player to the camera (Again
	// player is a entity as collisions occur in entities i have to update the camera
	// this way to make sure the transition occurs accordingly
	{camera.SetXPosition(mPosition.x); camera.SetZPosition(mPosition.z);}
}