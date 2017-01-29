/*
This class is a wrapper class currently for the Camera Class in the engine. As this game is a first person
that means the camera is the player. However having code such as Collision detection and shooting makes the camera
class a bit bloated. So I wanted to keep the camera class seperate and just worry about the view itself rather
than the extra things. So this class handles all those things for the Camera as well as updating the camera
as necessary

Author : Romesh Selvanathan
*/ 

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameUtil.h"
#include "IEnemyListener.h"
#include "Entity.h"
#include "Camera.h"
#include "IPortalListener.h"

class Player : public Entity, public IPortalListener
{
public:
	/* Construstor */
	Player(CVector3 position, CVector3 lookAt, CVector3 Up);
	/* Destructor */
	virtual ~Player();

	////////////////////////////////////Entity Inherited Method//////////////////////////
	bool Init(){return true;}
	/////////////////////////////////////////////////////////////////////////////////////

	/* Update this object */ 
	void Update(float dt);
	/* Render this object onto the scren */
	void Render();

	/* Obtain the Current Position of the camera */ 
	CVector3 Position(){return camera.Position();}
	/* Set if the player is sprinting or not */ 
	void SetIsSprinting(bool v) {sprint = v;}

	/* Shoots a Bullet at the current view direction */ 
	void ShootBullet();

	/* Move Player */ 
	void MovePlayer(float speed);
	/* Allow the player to strafe */ 
	void StrafePlayer(float speed);
	/* Allow the player to look around */ 
	void SetViewByMouse(float x, float y);

	////////////////////////////////////////IPortalListener////////////////////////
	void OnPortalEnter(int portal);
	///////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////ENTITY CLASS METHODS/////////////////////////
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	///////////////////////////////////////////////////////////////////////////////

	/* Add Listeners */ 
	void AddListener(SmartPtr<IEnemyListener> lptr){mListeners.push_back(lptr);}
	/*  Fire message to all listeners */ 
	void FireEnemyAttack(){
		for(ListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it++)
			(*it)->OnEnemyAttack();
	}

private:
	CCamera camera;						// The camera class itself
	
	bool move, sprint;					// whether the player should move, and whether the player is sprinting
	float m_speed;						// current speed of the player
    bool m_hasAttacked;					// has the player been attacked recently
	int m_tillNextAttack;				// time till next attack is allowed

	typedef list<SmartPtr<IEnemyListener>> ListenerList;
	ListenerList mListeners;			// List of all listeners
};

#endif