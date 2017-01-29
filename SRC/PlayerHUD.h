/*
A Player HUD class that will contain all the Player GUI such as health and energy.
Author : Romesh Selvanathan
*/

#ifndef __PLAYERHUD_H__
#define __PLAYERHUD_H__

#include "IPlayerListener.h"
#include "PlayerManager.h"
#include "ScoreKeeper.h"
#include "IScoreListener.h"
#include "GL2DBox.h"

class GLText;
class GL2DText;

class PlayerHUD : public IPlayerListener, public IScoreListener
{
public:
	/* Construstor */
	PlayerHUD();
	/* Destructor */
	~PlayerHUD();

	////////////////////////////////IPLAYERLISTENER////////////////////
	void OnHealthChanged(int health);
	void OnEnergyChanged(int energy);

	////////////////////////////////ISCORELISTENER/////////////////////
	void OnScoreChanged(int score);

	/* Render this object onto the scren */
	void Render();

	// Set the time value 
	void SetTime(int time){m_time = time;}

	// Set this Object as a listener to Playermanager class
	void SetPlayerListener(PlayerManager& mPlayerManager)
	{mPlayerManager.AddListener(this);}
	// Set this Object as a listener to Scorekeeper class
	void SetScoreListener(ScoreKeeper& mScoreKeeper)
	{mScoreKeeper.AddListener(this);}

private:
	float healthBarWidth;			// Width of the Health Bar
	float energyBarWidth;			// Width of Energy Bar

	SmartPtr<GLText> mTimeText;		// Text for time
	int m_time;						// current time

	SmartPtr<GLText> mScoreText;	// Text for score
	int m_score;					// current score

	SmartPtr<GLText> mHelpText;		// Help Text
	SmartPtr<GLText> mHelpText2;	// Help text 2

	GL2DBox health;					// Boxes to show health bar
	GL2DBox healthback;
	GL2DBox healthborder;

	GL2DBox energy;					// Boxes to show Energy bar
	GL2DBox energyback;
	GL2DBox energyborder;
};

#endif