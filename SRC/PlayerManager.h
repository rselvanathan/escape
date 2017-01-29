/*
This Class Manages all of its liseners and will update them with any Player related values

Author : Romesh Selvanathan
*/ 

#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "GameUtil.h"
#include "IEnemyListener.h"
#include "IPowerUpListener.h"
#include "IPlayerListener.h"

class PlayerManager : public IEnemyListener, public IPowerUpListener
{
public:
	/* Constructor */ 
	PlayerManager(){mHealth = 100; mEnergy = 100;}

	/* Reset this object */ 
	void Reset() {mHealth = 100; mEnergy = 100;}

	/////////////////////////////////////////IENEMYLISTENER/////////////////////////////////
	/* If enemy attack Player decrease health */ 
	void OnEnemyAttack(){
		mHealth -= 10;
		if(mHealth<0) {mHealth = 0;}

		mEnergy -= 10;
		if(mEnergy<0) {mEnergy = 0;}

		FireHealthChanged();
		FireEnergyChanged();
	}
	/////////////////////////////////////////IPOWERUPLISTENER//////////////////////////////
	void OnHealthPowerPicked()
	{
		// Increase health if power up is picked up
		mHealth += 40;
		// limit value to 100 max
		if(mHealth > 100) {mHealth = 100;}

		FireHealthChanged();
	}
	void OnEnergyPowerPicked()
	{
		// Increase energy if power up is picked up
		mEnergy += 30;
		// limit value to 100 max
		if(mEnergy > 100) {mEnergy = 100;}

		FireEnergyChanged();
	}
	///////////////////////////////////////////////////////////////////////////////////////

	/* Updates the mEnergy value where as long as it is below 100 constantly increase by a set amount */ 
	void Update(float dt)
	{
		if(mEnergy < 100){
			mEnergy += 45 * dt;
			FireEnergyChanged();
		}
	}

	/* A method that decreases energy by an amount whenever the player shoots */ 
	void PlayerShot() 
	{
		if (mEnergy <= 100) {
			mEnergy -= 20;
			if(mEnergy<0) {mEnergy = 0;}
			FireEnergyChanged();
		}
	}

	/* A method that decreases energy by and amount whenever the player sprints */ 
	void PlayerSprint(float dt)
	{
		if (mEnergy <= 100) {
			mEnergy -= 0.2*dt;
			if(mEnergy<0) {mEnergy = 0;}
			FireEnergyChanged();
		}
	}

	/* Add A listener to the list */ 
	void AddListener(SmartPtr<IPlayerListener> listener){mListeners.push_back(listener);}
	/* Fire the Change in health to all its Listeners */ 
	void FireHealthChanged()
	{
		for(PlayerListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit)
			(*lit)->OnHealthChanged(mHealth);
	}
	void FireEnergyChanged()
	{
		for(PlayerListenerList::iterator lit = mListeners.begin(); lit != mListeners.end(); ++lit)
			(*lit)->OnEnergyChanged(mEnergy);
	}

private:
	int mHealth; // The Health value set to 100
	int mEnergy; // The Energy value set to 100

	typedef list< SmartPtr<IPlayerListener> > PlayerListenerList;
	PlayerListenerList mListeners;
};

#endif 