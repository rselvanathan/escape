/* 
This class will hold all the game objects that will be in the game world and will update and Render them
This class will also update the Collision Detection in the world. This Class also send messages to its listener
when a object has been added or removed.
(PROBLEM SmartPtr causing removal problems, so using normal pointers)

Author : Romesh Selvanathan
*/ 

#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "CollisionManager.h"
#include "GameObject.h"
#include "IGameWorldListener.h"
#include "Entity.h"
#include <list>
#include "SmartPtr.h"

class GameWorld
{
public:
	/* Constructor */
	GameWorld();
	/* Destructor */
	~GameWorld();

	/* Reset this game world */
	void Reset();
	/* Update all objects in the game world */
	void Update(float dt);
	/* Render all objects in the game world */
	void Render();

	/* Add a GameObject into the game world */
	void AddGameObject(GameObject* lptr)
	{
		// Set the Objects Game World as this
		lptr->SetGameWorld(this);
		// Push back a game object
		mGameObjects.push_back(lptr);
		// Fire message to all listeners on which object was added
		FireObjectAdded(lptr);
	}
	/* Remove a game object from the game world */
	void RemoveGameObject(GameObject* lptr){
		/* remove the game Object */
		mGameObjects.remove(lptr);
		/* Remove the game object from the collision list */
		mCollisions.RemoveCollisionListener(lptr);
		/* make sure to set the objects game world to null */
		lptr->SetGameWorld(NULL);
		// Fire to all listeners on which game object was removed
		FireObjectRemoved(lptr);
	}

	/* Add listener */
	void AddListener( IGameWorldListener* lptr) { mListeners.push_back(lptr); }
	/* Remove listener */
	void RemoveListener( IGameWorldListener* lptr) { mListeners.remove(lptr); }
	/* Send Messages to all listeners */
	void FireObjectAdded(GameObject* ptr) {
		for (GameWorldListenerList::iterator it = mListeners.begin(); it != mListeners.end(); ++it)
			(*it)->OnObjectAdded(this, ptr);
	}
	void FireObjectRemoved(GameObject* ptr){
		for (GameWorldListenerList::iterator it = mListeners.begin(); it != mListeners.end(); ++it)
			(*it)->OnObjectRemoved(this, ptr);
	}

	/* Add Collision Entity */ 
	void AddCollisionEntity(Entity* lptr) {mCollisions.AddCollisionListener(lptr);}
	/* Add a Plane Entity */
	void AddPlaneEntity(SmartPtr<Entity> lptr) {mCollisions.AddPlaneListener(lptr);}
private:
	CollisionManager mCollisions;								// The Collision Manager

	typedef list<IGameWorldListener*> GameWorldListenerList;
	GameWorldListenerList mListeners;							// List of listeners
	
	typedef list< GameObject* > GameObjectList;
	GameObjectList mGameObjects;								// List of game objects
};

#endif 