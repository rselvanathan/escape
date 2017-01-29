/*
This class notifies messages to the player whenever an special event occurs. Such as low health
or score multiplier has been obtained/lost (This works a bit like the PlayerHUD but instead uses 
GL2DText)

Author : Romesh Selvanathan
*/

#ifndef __NOTIFYMESSAGE_H__
#define __NOTIFYMESSAGE_H__

#include "IGameWorldListener.h"
#include "IEnemyListener.h"
#include "IPlayerListener.h"
#include "GameUtil.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "IPortalListener.h"

class GL2DText;	

class NotifyMessage : public IGameWorldListener, public IEnemyListener, public IPlayerListener,
					  public IPortalListener
{
public:
	/* Construstor */ 
	NotifyMessage();
	/* Destructor */
	~NotifyMessage();

	/* Reset this object */
	void Reset();
	/* Update this object */ 
	void Update(float dt);
	/* Render this object onto the scren */
	void Render();

	//////////////////////////////IGAMEWORLD///////////////////////////////////////
	void OnObjectRemoved(GameWorld* world, GameObject* object);
	void OnObjectAdded(GameWorld* world, GameObject* object){}
	//////////////////////////////ENEMY/////////////////////////////////////////////
	void OnEnemyAttack();
	/////////////////////////////Player/////////////////////////////////////////////
	void OnHealthChanged(int health);
	void OnEnergyChanged(int energy){}
	///////////////////////////////////////////////////////////////////////////////
	////////////////////////////Portal//////////////////////////////////////////////
	void OnPortalEnter(int portal);
	//////////////////////////////////////////////////////////////////////////////

private:
	typedef list<GL2DText*> ScoreList;
	ScoreList mScores;						// A list of Score texts

	SmartPtr<GL2DText> mNotifyMultiplier;
	bool showMulti;							// whether to show the multiplier has been gained
	int mTTLMulti;							// time till this message stays alive
	// This value makes sure that if multiplier is gained and message has been shown already
	// do not show it again unless player loses the multiplier 
	bool multiGained; 

	SmartPtr<GL2DText> mNotifyMultiLost;
	bool showMultiLost;						// whether to show the multiplier has been lost
	int mTTLMultiLost;						// time till this message stays alive
	// Same Reason as multiGained but this is for when multiplier iss lost
	bool  multiLost;

	SmartPtr<GL2DText> mNotifyHealth;
	bool showLowHealth;						// whether to show the low health 
	float scale, rand;	// scale to alow text to pulsate and rand (just a random value that is constantly being added)

	SmartPtr<GL2DText> mNotifyIntro;
	bool showIntro;							// whether to show the intro message when game starts
	int mTTLIntro;							// time till this message stays alive

	SmartPtr<GL2DText> mNotifySecondStage;
	bool showStage2;						// whether to show the message in the second stage of the game
	int mTTLStage2;							// time till this message stays alive
};

#endif 