/* 
This class will hold all the game objects that will be in the game world and will update and Render them
This class will also update the Collision Detection in the world. This Class also send messages to its listener
when a object has been added or removed.
(PROBLEM SmartPtr causing removal problems, so using normal pointers)

Author : Romesh Selvanathan
*/ 

#include "GameWorld.h"
#include "CollisionManager.h"
#include "GameObject.h"

/* Constructor */
GameWorld::GameWorld()
{}
/* Destructor */
GameWorld::~GameWorld()
{}

/* Reset this game world */
void GameWorld::Reset()
{
	mCollisions.Reset();
	mListeners.clear();
	mGameObjects.clear();
}

/* Update all objects in the game world */
void GameWorld::Update(float dt)
{
	// Update all Collisions
	mCollisions.UpdateCollision();

	GameObjectList::iterator object = mGameObjects.begin();
	while(object != mGameObjects.end()){
		// keep a copy just in case a object is deleted (Safety check )
		GameObjectList::iterator copy = object++;
		(*copy)->UpdateGravity(dt);
		(*copy)->Update(dt);
	}
}

/* Render all objects in the game world */
void GameWorld::Render()
{
	for(GameObjectList::iterator object = mGameObjects.begin(); object != mGameObjects.end(); object++)
	{
		(*object)->PreRender();
		(*object)->Render();
		(*object)->PostRender();
	}
}
