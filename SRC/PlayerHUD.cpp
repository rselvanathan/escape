/*
A Player HUD class that will contain all the Player GUI such as health and energy.
Author : Romesh Selvanathan
*/

#include "PlayerHUD.h"
#include "GameUtil.h"
#include "PreLoader.h"
#include "GLTexture.h"
#include "GLText.h"
#include "GL2DBox.h"

/* Constructor */
PlayerHUD::PlayerHUD() : healthBarWidth(400), energyBarWidth(400), m_score(0), m_time(0)
{
	mTimeText = new GLText();
	mTimeText->CreateText(-24, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
	mTimeText->SetPosition(330, 500);
	mTimeText->SetColor3f(1, 0, 0);

	mScoreText = new GLText();
	mScoreText->CreateText(-24, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
	mScoreText->SetPosition(330, 450);
	mScoreText->SetColor3f(1, 1, 0);

	mHelpText = new GLText();
	mHelpText->CreateText(-12, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
	mHelpText->SetColor3f(1, 1, 1);
	mHelpText->SetPosition(0, 500);

	mHelpText2 = new GLText();
	mHelpText2->CreateText(-12, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
	mHelpText2->SetColor3f(1, 1, 1);
	mHelpText2->SetPosition(0, 470);

	health.Init(400, 10, 200, 80);
	health.SetColor(1, 0, 0, 1);
	healthback.Init(400, 10, 200, 80);
	healthback.SetColor(1, 1, 1, 1);
	healthborder.Init(400, 15, 200, 80);
	healthborder.SetColor(0, 0, 0, 1);

	energy.Init(400, 10, 200, 40);
	energy.SetColor(1, 1, 0, 1);
	energyback.Init(400, 10, 200, 40);
	energyback.SetColor(1, 1, 1, 1);
	energyborder.Init(400, 15, 200, 40);
	energyborder.SetColor(0, 0, 0, 1);
}

/* Destructor */
PlayerHUD::~PlayerHUD()
{
	SAFE_DELETE(mTimeText);
	SAFE_DELETE(mScoreText);
	SAFE_DELETE(mHelpText);
	SAFE_DELETE(mHelpText2);
}

/////////////////////////////////////////////IPLAYERLISTENER////////////////////////////////////

/* METHOD FROM IPLAYERLISTENER : This method listens to the current health of the player
	and will change the width of the health bar accordingly*/ 
void PlayerHUD::OnHealthChanged(int Health)
{
	// NOTE : its x 4 - because the health value is 100 in total so the bar width is 400 here
	// meaning 400 / 100 = 4. So to obtain the width properly i multiply the health by 4
	healthBarWidth = (Health * 4);
	// limit the width to 400
	if(healthBarWidth > 400)
		healthBarWidth = 400;
	// set the width of the 2D box to this
	health.SetWidth(healthBarWidth);
}
/* METHOD FROM IPLAYERLISTENER : This method listens to the current energy of the player
	and will change the width of the energy bar accordingly*/ 
void PlayerHUD::OnEnergyChanged(int Energy)
{
	// NOTE : its x 4 - because the energy value is 100 in total so the bar width is 400 here
	// meaning 400 / 100 = 4. So to obtain the width properly i multiply the energy by 4
	energyBarWidth = (Energy * 4);
	// limit the width to 400
	if(energyBarWidth> 400)
		energyBarWidth = 400;
	// set the width of the 2D box to this
	energy.SetWidth(energyBarWidth);
}

////////////////////////////////////////////ISCORELISTENER///////////////////////////////////////
/* METHOD FROM ISCORELISTENER : This method listens to the current score of the player
	and will change the score text accordingly*/ 
void PlayerHUD::OnScoreChanged(int score)
{
	m_score = score;
}

/* Render the HUD */ 
void PlayerHUD::Render()
{
	mHelpText2->print(" Press E to sprint ");
	mHelpText->print(" Press Q to shoot ");
	mTimeText->print("Time - %i", m_time);
	mScoreText->print("Score - %i", m_score);

	health.Render();
	healthback.Render();
	healthborder.Render();

	energy.Render();
	energyback.Render();
	energyborder.Render();
}