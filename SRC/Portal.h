/*
These Portals allow th eplayer to move from one part of the world to another. There are currently
2 portals one that moves from the first part of the world to the second and another which allows
the player to complete the game

Author : Romesh Selvanathan
*/ 

#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "ISwitchListener.h"
#include "IPortalListener.h"

class Portal : public GameObject, public ISwitchListener
{
public :
	/* Constructor */
	Portal(const char* name);
	/* Destructor */ 
	virtual ~Portal();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////ISWITCHLISTENER///////////////////////////////////////////////
	void OnSwitchTurned(bool _blue, bool _red);
	void OnSwitchTurned2(bool _blue, bool _red, bool _yellow);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Add Listeners */ 
	void AddListeners(SmartPtr<IPortalListener> lptr) {mListeners.push_back(lptr);}
	/*  Fire message to all listeners */ 
	void FireOnPortalEntered(int portal)
	{
		for(ListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it ++)
			(*it)->OnPortalEnter(portal);
	} 

private:
	bool red, blue;							// The first set of switches
	bool red2, blue2, yellow2;				// The second set of switches
	SmartPtr<Model_3DS> p_Model;			// The 3D model for the portal

	typedef list<SmartPtr<IPortalListener>> ListenerList;
	ListenerList mListeners;				// Listeners to this object
};


#endif