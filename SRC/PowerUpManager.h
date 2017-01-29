/*
This Class Manages all of its liseners and will update them with any Powerup related values

Author : Romesh Selvanathan
*/ 

#ifndef __POWERUPMANAGER_H__
#define __POWERUPMANAGER_H__

#include "IPowerUpListener.h"
#include "IGameWorldListener.h"
#include "GameObject.h"
#include "GameObjectType.h"
#include "GameUtil.h"

class PowerUpManager : public IGameWorldListener
{
public:
	/* Constructor */ 
	PowerUpManager(){}

	////////////////////////////////////////////IGAMEWORLDLISTENER//////////////////////////////////////
	void OnObjectAdded(GameWorld* world, GameObject* object){}
	void OnObjectRemoved(GameWorld* world, GameObject* object)
	{
		// if power up health is removed
		if(object->GetType() == GameObjectType("poweruphealth"))
			FireOnHealthPicked();
		// if energy power up if removed
		if(object->GetType() == GameObjectType("powerupenergy"))
			FireOnEnergyPicked();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////

	/* Add A listener to the list */ 
	void AddListener(SmartPtr<IPowerUpListener> ptr) {mListeners.push_back(ptr);}
	/* Fire messages to all its Listeners */ 
	void FireOnHealthPicked()
	{
		for(PowerListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it ++)
			(*it)->OnHealthPowerPicked();
	}
	void FireOnEnergyPicked()
	{
		for(PowerListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it ++)
			(*it)->OnEnergyPowerPicked();
	}
	
private:
	typedef list< SmartPtr< IPowerUpListener > > PowerListenerList;
	PowerListenerList mListeners;
};

#endif