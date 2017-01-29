/*
This Class Manages all of its liseners and will update them with any Score related values

Author : Romesh Selvanathan
*/ 

#ifndef __SCOREKEEPER_H__
#define __SCOREKEEPER_H__

#include "IGameWorldListener.h"
#include "IScoreListener.h"
#include "IEnemyListener.h"
#include "GameObject.h"
#include "GameObjectType.h"
#include "GameUtil.h"

class ScoreKeeper : public IGameWorldListener, public IEnemyListener
{
public:
	/* Constructor */ 
	ScoreKeeper() : score(0), scoreMultiplier(1) {}

	/* Reset this object */ 
	void Reset() {score = 0; scoreMultiplier = 1;}

	////////////////////////////////////////////IGAMEWORLDLISTENER//////////////////////////////////////
	void OnObjectAdded(GameWorld* world, GameObject* object){}
	void OnObjectRemoved(GameWorld* world, GameObject* object)
	{
		// If coin is removed from the world increase the score by value
		if(object->GetType() == GameObjectType("coin")){
			score += (10*scoreMultiplier);
			FireScoreChanged();
		}
		// if enemy is removed from the world then increase score as well as the multiplier by a value
		if(object->GetType() == GameObjectType("enemy")){
			score += (30*scoreMultiplier);
			scoreMultiplier = 2;
			FireScoreChanged();
		}
	}
	////////////////////////////////////////////IENEMYLISTENER//////////////////////////////////////
	void OnEnemyAttack()
	{
		scoreMultiplier = 1;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////

	/* Add A listener to the list */ 
	void AddListener(SmartPtr<IScoreListener> ptr) {mListeners.push_back(ptr);}
	/* Fire messages to all its Listeners */ 
	void FireScoreChanged(){
		for(ScoreListenerList::iterator it = mListeners.begin(); it != mListeners.end(); it++)
			(*it)->OnScoreChanged(score);
	}
private:	
	int score;							// current score
	int scoreMultiplier;				// current score multiplier value

	typedef list< SmartPtr<IScoreListener> > ScoreListenerList;
	ScoreListenerList mListeners;
};

#endif