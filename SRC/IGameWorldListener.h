#ifndef __IGAMEWORLDLISTENER_H__
#define __IGAMEWORLDLISTENER_H__

#include "GameUtil.h"
#include "SmartPtr.h"

class GameWorld;
class GameObject;

class IGameWorldListener
{
public:
	virtual void OnObjectAdded(GameWorld* world, GameObject* object) = 0;
	virtual void OnObjectRemoved(GameWorld* world, GameObject* object) = 0;
};

#endif