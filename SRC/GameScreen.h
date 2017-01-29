/*
This class Sets up the game screen itself loading everything required for the game. This class
will obtain the difficulty value from the menu screen and set the timer up accordingly. It will also
pass the score value to the game over screen when the game has finished. IF the players health is finished or if 
the player manages to finish the game the whole game will stop rendering and the only thing that this screen
allows is to press C to continue onto the game over screen.

Author : Romesh Selvanathan
*/

#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "GameUtil.h"
#include "PlayerManager.h"
#include "ScoreKeeper.h"
#include "PowerUpManager.h"
#include "GameWorld.h"
#include "IKeyboardListener.h"
#include "IMouseListener.h"
#include "IPlayerListener.h"
#include "IPortalListener.h"
#include "IScoreListener.h"
#include "NotifyMessage.h"
#include "CRandom.h"
#include "GLFog.h"
#include "GLLight.h"
#include "Timer.h"
#include "InputManager.h"
#include <fstream>

#define CAMERA_SPEED 40.f				// Speed of the player when walking
#define CAMERA_SPRINT_SPEED 150.f		// Speed of the player when sprinting

#define MAX_TREES 20					// Maximum number of trees
#define MAX_ENEMY 7						// Maximum number of enemies
#define MAX_COINS 16					// Maximum number of coins
#define MAX_POWERUPS 5					// Maximum number of powerups

class CCamera;
class Skybox;
class QuadTerrain;
class TestSquare;
class Enemy;
class Tree;
class PlayerHUD;
class VerticalWall;
class HorizontalWall;
class Shoot;
class Portal;
class Switch;
class Coin;
class PowerUp;
class Player;
class GL2DText;

class GameScreen : public IKeyboardListener, public IMouseListener, public IPlayerListener, public IScoreListener,
					public IPortalListener
{
public:
	/* Constructor */
	GameScreen(){}
	/* Destructor */
	~GameScreen();

	/* Initialise the game */ 
	void Init(int state);
	/* Update the Object */ 
	void Update(float dt);
	/* Render this object onto the scren */
	void Render();

	/* Load in the trees */
	void LoadTrees();
	/* Load in the coins */
	void LoadCoins();
	/*Load in the Power ups */
	void LoadPowerUps();
	/* Load in the enemies */
	void LoadEnemies();

	/////////////////////////////////KEYBOARD///////////////////////////
	void OnKeyPressed(vector< char* > mKeyList);
	void OnKeyReleased(vector< char* > mKeyList);
	void OnKeyPressAndRelease(char* key){}
	////////////////////////////////////////////////////////////////////

	/////////////////////////////////KEYBOARD///////////////////////////
	void OnMouseMove(float x, float y);
	////////////////////////////////////////////////////////////////////

	///////////////////////////////PLAYER///////////////////////////////
	void OnHealthChanged(int health);
	void OnEnergyChanged(int energy);
	////////////////////////////////////////////////////////////////////

	///////////////////////////////Score////////////////////////////////
	void OnScoreChanged(int score) {m_score = score;}
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////IPortalListener/////////////
	void OnPortalEnter(int portal);
	////////////////////////////////////////////////////////////////////

	/* Return if the switching of screen state should occur */
	const bool GetStateSwitch() const {return mStateSwitch;}
	/* Return the current score of the player */ 
	const int GetScore() const {return m_score;}

	// Turn this screen into a keyboard listener
	void SetInput(InputManager* mInput) {mInput->AddKeyboardListener(this); mInput->AddMouseListener(this);}

	/* States for the difficulty of the game - (used for timer) */ 
	enum {EASY, HARD};
private:
	Player* mPlayer;						
	Skybox* p_Skybox;						
	PlayerHUD* mPlayerHUD;

	QuadTerrain* p_Terrain;
	Enemy* mEnemy[MAX_ENEMY];
	Tree* mTree[MAX_TREES];

	Coin* mCoin[MAX_COINS];
	PowerUp* mPowerUp[MAX_POWERUPS];

	///////////////////////////Inside Walls///////////////////////////////
	TestSquare* mRedSquare;
	TestSquare* mBlueSquare;
	Portal* mPortal;
	Switch* mRedSwitch;
	Switch* mBlueSwitch;
	HorizontalWall* mWallLeft;
	HorizontalWall* mWallRight;
	VerticalWall* mWallBack;
	VerticalWall* mWall;
	///////////////////////////////////////////////////////////////////////

	///////////////////////////Outside Walls///////////////////////////////
	Switch* mRedSwitch2;
	Switch* mBlueSwitch2;
	Switch* mYellowSwitch2;
	TestSquare* mRedSquare2;
	TestSquare* mBlueSquare2;
	TestSquare* mYellowSquare2;
	Portal* mPortal2;
	///////////////////////////////////////////////////////////////////////

	ScoreKeeper mScoreKeeper;
	PlayerManager mPlayerManager;
	PowerUpManager mPowerUpManager;
	NotifyMessage mNotify;
	GameWorld mWorld;
	CRandom random;
	Timer mTimer;

	GLFog fog;
	GLLight light;
	GLLight light2;
	GLLight light3;

	float cameraSpeed;					// current speed of the player
	float cameraSpeedType;				// the type of speed 
	bool m_hasShot, m_sprinting;		// has the player shot recently and is the player sprinting
	int m_tillNextShot;					// time till next shot is allowed
	int m_energy, m_score;				// current energy and score of the player
	bool m_gameComplete;				// has the game been completed successfully

	bool mStateSwitch;					// Should the screen state be switched
	bool mGameOver;						// has the player lost

	GL2DText* gameOverMessage;			// Game Over message
	GL2DText* pressEnterMessage;		// The press continue message
};

#endif