/*
This class Sets up the game screen itself loading everything required for the game. This class
will obtain the difficulty value from the menu screen and set the timer up accordingly. It will also
pass the score value to the game over screen when the game has finished. IF the players health is finished or if 
the player manages to finish the game the whole game will stop rendering and the only thing that this screen
allows is to press C to continue onto the game over screen.

Author : Romesh Selvanathan
*/
#include <fstream>
#include "GameScreen.h"
#include "GameUtil.h"
#include "Skybox.h"
#include "QuadTerrain.h"
#include "TestSquare.h "
#include "Enemy.h"
#include "Tree.h"
#include "PlayerHUD.h"
#include "PlayerManager.h"
#include "PowerUpManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "VerticalWall.h"
#include "HorizontalWall.h"
#include "IKeyboardListener.h"
#include "Portal.h"
#include "Switch.h"
#include "Coin.h"
#include "PowerUp.h"
#include "GLFog.h"
#include "Graphics.h"
#include "Light.h"
#include "Player.h"
#include "NotifyMessage.h"
#include "GL2DText.h"


/* Destructor */ 
GameScreen::~GameScreen()
{
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(p_Skybox);
	SAFE_DELETE(mPlayerHUD);
	SAFE_DELETE(p_Terrain);
	SAFE_DELETE(mWall);
	SAFE_DELETE(mWallBack);
	SAFE_DELETE(mWallLeft);
	SAFE_DELETE(mWallRight);
	for(int i = 0 ; i < MAX_ENEMY; i ++)
		SAFE_DELETE(mEnemy[i]);
	for(int i = 0; i < MAX_TREES; i++)
		SAFE_DELETE(mTree[i]);
	for(int i = 0; i < MAX_COINS; i++)
		SAFE_DELETE(mCoin[i]);
	for(int i = 0; i < MAX_POWERUPS; i++)
		SAFE_DELETE(mPowerUp[i]);
	/////////////////////////
	SAFE_DELETE(mRedSquare);
	SAFE_DELETE(mBlueSquare);
	SAFE_DELETE(mPortal);
	SAFE_DELETE(mRedSwitch);
	SAFE_DELETE(mBlueSwitch);
	//////////////////////////
	SAFE_DELETE(mRedSwitch2);
	SAFE_DELETE(mBlueSwitch);
	SAFE_DELETE(mYellowSwitch2);
	SAFE_DELETE(mRedSquare2);
	SAFE_DELETE(mBlueSquare2);
	SAFE_DELETE(mYellowSquare2);
	SAFE_DELETE(mPortal2);
}

/* Initialise this class */ 
void GameScreen::Init(int state)
{
	// Initialise all the values
	cameraSpeed = 0.0f;
	cameraSpeedType = CAMERA_SPEED;
	m_score = 0;
	m_energy = 100;
	m_tillNextShot = 50;
	m_hasShot = m_sprinting =  false;
	mStateSwitch = false;
	mGameOver = false;
	m_gameComplete = false;
	mGameOver = false;

	// Init the Random Number Generator
	random.Randomize();

	/* Reset classes that require resets */
	mPlayerManager.Reset();
	mScoreKeeper.Reset();
	mNotify.Reset();
	mWorld.Reset();
	light.Reset();

	p_Skybox = new Skybox();
	p_Skybox->CreateSkyboxTextures();	//Load our skybox textures

	p_Terrain = new QuadTerrain(0.5, CVector3(0, 0, 0));
	
	mPlayer = new Player(CVector3(250, 35, 500), CVector3(0, 1.0, 0.5), CVector3(0, 1, 0));
	//g_Camera->PositionCamera( CVector3(250, 35, 500), CVector3(0, 1.0, 0.5), CVector3(0, 1, 0));
	/*g_Camera->PositionCamera( CVector3(500, 35, 500), CVector3(0, 1.0, 0.5), CVector3(0, 1, 0));*/
	mPlayer->SetGameWorld(&mWorld);
	mPlayer->AddListener(&mPlayerManager);
	mPlayer->AddListener(&mScoreKeeper);
	mPlayer->AddListener(&mNotify);

	mWorld.AddCollisionEntity(mPlayer);

	/////////////////////////////////////Inside Walls //////////////////////////////////////////////
	mPortal = new Portal("portal");
	mPortal->SetPosition(CVector3(100, 2, 500));
	mPortal->SetRotation(0, 90, 0);
	mPortal->SetGroundValue(2);
	mPortal->SetColor(1.0f, 1.0f, 1.f);

	mRedSwitch = new Switch("redswitch");
	mRedSwitch->SetPosition(CVector3(400, 2, 300));
	mRedSwitch->SetColor(1.0f, 0.0f, 0.f);
	mRedSwitch->SetScale(0.5);
	mRedSwitch->SetGroundValue(2);

	mBlueSwitch = new Switch("blueswitch");
	mBlueSwitch->SetPosition(CVector3(400, 2, 700));
	mBlueSwitch->SetColor(0.0f, 0.0f, 1.f);
	mBlueSwitch->SetScale(0.5);
	mBlueSwitch->SetGroundValue(2);

	mBlueSwitch->AddListener(mPortal);
	mRedSwitch->AddListener(mPortal);

	mRedSquare = new TestSquare("redsquare");
	mRedSquare->SetPosition(CVector3(300, 100, 580));
	mRedSquare->SetColor(1, 0, 0);

	mBlueSquare = new TestSquare("bluesquare");
	mBlueSquare->SetPosition(CVector3(300, 100, 380));
	mBlueSquare->SetColor(0, 0, 1);

	mWall = new VerticalWall(CVector3(250, 20, 200));
	mWallBack = new VerticalWall(CVector3(250, 20, 800));
	mWallLeft = new HorizontalWall(CVector3(50, 20, 500));
	mWallRight = new HorizontalWall(CVector3(450, 20, 500));

	mWorld.AddGameObject(mWall);
	mWorld.AddGameObject(mWallBack);
	mWorld.AddGameObject(mWallLeft);
	mWorld.AddGameObject(mWallRight);
	mWorld.AddGameObject(mPortal);
	mWorld.AddGameObject(mRedSwitch);
	mWorld.AddGameObject(mBlueSwitch);
	mWorld.AddGameObject(mRedSquare);
	mWorld.AddGameObject(mBlueSquare);

	mWorld.AddCollisionEntity(mPortal);
	mWorld.AddCollisionEntity(mWall);
	mWorld.AddCollisionEntity(mWallBack);
	mWorld.AddCollisionEntity(mWallLeft);
	mWorld.AddCollisionEntity(mWallRight);
	mWorld.AddCollisionEntity(mRedSwitch);
	mWorld.AddCollisionEntity(mBlueSwitch);
	mWorld.AddCollisionEntity(mRedSquare);
	mWorld.AddCollisionEntity(mBlueSquare);

	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////Outside Walls///////////////////////////////////////////////

	mPortal2 = new Portal("portal2");
	mPortal2->SetPosition(CVector3(600, 2, -300));
	mPortal2->SetRotation(0, 90, 0);
	mPortal2->SetGroundValue(2);

	mRedSwitch2 = new Switch("redswitch2");
	mRedSwitch2->SetPosition(CVector3(1500, 0, 1000));
	mRedSwitch2->SetColor(1.0f, 0.0f, 0.f);
	mRedSwitch2->SetScale(0.5);
	mRedSwitch2->SetGroundValue(0);

	mBlueSwitch2 = new Switch("blueswitch2");
	mBlueSwitch2->SetPosition(CVector3(500, 0, 1500));
	mBlueSwitch2->SetColor(0.0, 0.0f, 1.f);
	mBlueSwitch2->SetScale(0.5);
	mBlueSwitch2->SetGroundValue(0);

	mYellowSwitch2 = new Switch("yellowswitch2");
	mYellowSwitch2->SetPosition(CVector3(200, 0, -400));
	mYellowSwitch2->SetColor(1.0, 1.0f, 0.f);
	mYellowSwitch2->SetScale(10);
	mYellowSwitch2->SetGroundValue(0);

	mBlueSwitch2->AddListener(mPortal2);
	mRedSwitch2->AddListener(mPortal2);
	mYellowSwitch2->AddListener(mPortal2);

	mRedSquare2 = new TestSquare("redsquare2");
	mRedSquare2->SetPosition(CVector3(1100, 100, 900));
	mRedSquare2->SetColor(1, 0, 0);

	mBlueSquare2 = new TestSquare("bluesquare2");
	mBlueSquare2->SetPosition(CVector3(400, 100, 1100));
	mBlueSquare2->SetColor(0, 0, 1);

	mYellowSquare2 = new TestSquare("yellowsquare2");
	mYellowSquare2->SetPosition(CVector3(100, 100, -200));
	mYellowSquare2->SetColor(1, 1, 0);

	mWorld.AddGameObject(mRedSwitch2);
	mWorld.AddGameObject(mBlueSwitch2);
	mWorld.AddGameObject(mYellowSwitch2);
	mWorld.AddGameObject(mRedSquare2);
	mWorld.AddGameObject(mBlueSquare2);
	mWorld.AddGameObject(mYellowSquare2);
	mWorld.AddGameObject(mPortal2);

	mWorld.AddCollisionEntity(mRedSwitch2);
	mWorld.AddCollisionEntity(mBlueSwitch2);
	mWorld.AddCollisionEntity(mYellowSwitch2);
	mWorld.AddCollisionEntity(mRedSquare2);
	mWorld.AddCollisionEntity(mBlueSquare2);
	mWorld.AddCollisionEntity(mYellowSquare2);
	mWorld.AddCollisionEntity(mPortal2);

	///////////////////////////////////////////////////////////////////////////////////////////////////

	// Load in the trees
	LoadTrees();
	// Load in the coins
	LoadCoins();
	// Load in the PowerUps
	LoadPowerUps();
	// Load in enemies 
	LoadEnemies();

	mPlayerHUD = new PlayerHUD();

	// Set up the Listeners that have not been set up yet */ 
	mPlayerHUD->SetPlayerListener(mPlayerManager);
	mPlayerHUD->SetScoreListener(mScoreKeeper);
	mPortal->AddListeners(this);
	mPortal->AddListeners(mPlayer);
	mPortal->AddListeners(&mNotify);
	mPortal2->AddListeners(this);
	mPortal2->AddListeners(mPlayer);
	mPortal2->AddListeners(&mNotify);
	mPlayerManager.AddListener(this);
	mPlayerManager.AddListener(&mNotify);
	mPowerUpManager.AddListener(&mPlayerManager);
	mScoreKeeper.AddListener(this);
	mWorld.AddListener(&mPowerUpManager);
	mWorld.AddListener(&mScoreKeeper);
	mWorld.AddListener(&mNotify);


	// Set up the Depth and Density of the fog
	fog.SetFogDensity(0.001);
	fog.SetFogDepth(1.0f, 5.0f);

	// Set the ambient color of the light
	light.SetAmbientColor(0, 0, 0, 0);

	// Setting up the Second light in the gameoworld which is slighlty green and positioned near the red switch outside
	light2.SetAmbientColor(0, 0, 0, 0);
	light2.SetDiffuseColor(0, 0.2, 0, 1);
	light2.SetSpecularColor(0, 0.5, 0, 1);
	light2.SetPosition(1100, 100, 900, 1);

	// Setting up the Second light in the gameoworld which is blue and positioned near the blue switch outside
	light3.SetAmbientColor(0, 0, 0, 0);
	light3.SetDiffuseColor(0, 0, 0.9, 1);
	light3.SetSpecularColor(0, 0, 0.5, 1);
	light3.SetPosition(500, 100, 1500, 1);

	// Initialise a new Timer
	mTimer.init();

	// Set the coundown start value depending on the difficulty level
	if(state == EASY)
		mTimer.SetCountdown(300);
	else if(state == HARD)
		mTimer.SetCountdown(105);

	gameOverMessage = new GL2DText();
	gameOverMessage->SetPosition(CVector3(240, 300, 0));
	gameOverMessage->SetScale(2);
	gameOverMessage->glSetColor(1, 0.5, 0, 1);

	pressEnterMessage = new GL2DText();
	pressEnterMessage->SetPosition(CVector3(250, 270, 0));
	pressEnterMessage->glSetColor(1, 0.8, 0, 1);
}

/* Update the Gamescreen */ 
void GameScreen::Update(float dt)
{ 
	// If the game has not finished then
	if(!mGameOver) {
		// Set the time value in player HUD to current timer value
		int t = mTimer.countdown();
		if(t <= 0)
			// IF the time is 0 then end the game
			mGameOver = true;
		mPlayerHUD->SetTime(t);

		// Update the Player First by working out the Player speed
		cameraSpeed = cameraSpeedType * dt;
		mPlayer->Update(dt);

		// For each enemy in the world
		for(int i = 0 ; i < MAX_ENEMY; i ++) {
			// IF the enemy pointer is not null (Safety Check)
			if(mEnemy[i] != NULL)
				// Set the player position variable in the enemy object to the current player position
				mEnemy[i]->SetPlayerPosition(mPlayer->Position());
		}
		
		// Update every single game object in the game world
		mWorld.Update(dt);

		// Update the PlayerManager class
		mPlayerManager.Update(dt);
		if(m_sprinting)
			// If sprinting then update the energy loss from sprinting
			mPlayerManager.PlayerSprint(dt);

		// if shoot has been pressed
		if(m_hasShot){
			// decrease value
			m_tillNextShot -= 100 *dt;
			// check to make sure it don't go below 0
			if(m_tillNextShot < 0) {m_tillNextShot = 0;}
			// if 0 reset the value and allow shooting again
			if(m_tillNextShot==0){
				m_hasShot = false;
				m_tillNextShot = 50;
			}
		}

		// Update the notify messages on screen
		mNotify.Update(dt);
	}
}

/* Render the screen */ 
void GameScreen::Render()
{
	// Switch on the Light
	light.PowerUpLight();
	// Enable A specific light
	light.SwitchOnLight(GL_LIGHT1);
	light2.SwitchOnLight(GL_LIGHT2);
	light3.SwitchOnLight(GL_LIGHT3);
	///////////////////////////////////////////////////////////////////////////////////////////////////

	// Clear the Screens Depth and Color Buffer
	Graphics::GetInstance()->ClearScreen();
	// IF the game has not ended
	if(!mGameOver)
		// Render the Player HUD
		mPlayerHUD->Render();

	// Reset the ModelView Matrix of the world
	Graphics::GetInstance()->ResetMatrix();

	CVector3 vNewPos    = mPlayer->GetPosition();
	// Render the current player 
	mPlayer->Render();
	
	p_Terrain->RenderQuadTerrain();

	//Draw the skybox
	p_Skybox->CreateSkyBox(vNewPos.x,  vNewPos.y,  vNewPos.z, 7000, 7000, 7000);

	// Render Every single object in the World
	mWorld.Render();

	// Render the Ligthts
	light.Render();
	light2.Render();
	light3.Render();

	// Render the Fog
	fog.Render();

	// If the Game has not finished render the messages to notify
	if(!mGameOver)
		mNotify.Render();

	// if the game has finished 
	if(mGameOver){
		char* message;
		// depnding on whether the game was completed or the player lost
		if(m_gameComplete)
			message = "  COMPLETE ! ";
		else
			message = " GAME OVER ! ";
		// Show the appropriate messages
		gameOverMessage->glPrint(message , GL2DText::NORMAL);
		pressEnterMessage->glPrint(" Press C to Continue ", GL2DText::NORMAL);
	}
}

/////////////////////////////////PLAYER///////////////////////////

void GameScreen::OnHealthChanged(int health)
{
	// Depending on the health value change the color of the world diffuse to raise tension
	if(health < 20)
		light.SetDiffuseColor(1, 0.0, 0.0, 1);
	else if( health < 40)
		light.SetDiffuseColor(1.0, 0.2, 0, 1);
	else if (health < 60)
		light.SetDiffuseColor(1.0, 0.5, 0, 1);
	else if (health < 80)
		light.SetDiffuseColor(1.0, 0.8, 0, 1);
	else 
		light.SetDiffuseColor(1, 1, 1, 1);

	// If health is below 0 then end the game
	if(health <= 0)
		mGameOver = true;
}

void GameScreen::OnEnergyChanged(int energy)
{
	m_energy = energy;
}

//////////////////////////////////////////////IPortalListener/////////////////////////////////////////
void GameScreen::OnPortalEnter(int portal)
{
	// If the second portal has been entered then end the game where the player succeded aswell 
	if(portal == 2){
		mGameOver = true; m_gameComplete = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////KEYBOARD///////////////////////////

void GameScreen::OnKeyPressed(vector< char* > mKeyList)
{
	for(int i = 0; i < mKeyList.size(); i ++){
		if(!mGameOver) {
			// Check if we hit the Up arrow or the 'w' key
			if(mKeyList[i] == "W")		
				// Move our player forward by a positive SPEED
				mPlayer->MovePlayer(cameraSpeed);

			// Check if we hit the Down arrow or the 's' key
			if(mKeyList[i] == "S")	
				// Move our player backward by a negative SPEED
				mPlayer->MovePlayer(-cameraSpeed);

			// Check if we hit the Left arrow or the 'a' key
			if(mKeyList[i] == "A")
				// Strafe the player left
				mPlayer->StrafePlayer(-cameraSpeed);

			// Check if we hit the Right arrow or the 'd' key
			if(mKeyList[i] == "D")	
				// Strafe the player right
				mPlayer->StrafePlayer(cameraSpeed);

			// Check if we hit the 'q' key
			if(mKeyList[i] == "Q")
				// Shoot only if shoot hasnt been done in specified time frame
				if(!m_hasShot){
					// and if the current energy is above 0
					if(m_energy > 0){
						// Shoot a bullet, and tell playermanager to decrease energy value accordingly
						mPlayer->ShootBullet(); m_hasShot = true;
						mPlayerManager.PlayerShot();
					}
				}
			// Check if we hit the 'e' key
			if(mKeyList[i] == "E"){
				// Cannot sprint if energy is below 0
				if(m_energy > 0){
					// Set the new camera speed type
					cameraSpeedType = CAMERA_SPRINT_SPEED;
					// tell the player that sprinting is allowed
					mPlayer->SetIsSprinting(true);
					// tell the player manager that player is sprinting to decrease energy value accordingly
					//m_sprinting = true;
				}
			}
			// otherwise
			else{
				// reset the camera speed
				cameraSpeedType = CAMERA_SPEED;
				// tell the player that sprinting is not allowed
				mPlayer->SetIsSprinting(false);
				m_sprinting = false;	
			}
		}
		// if the game has ended
		if(mGameOver){
			// Check if we hit the 'c' key
			if(mKeyList[i] == "C")
				// switch the state
				mStateSwitch = true;
		}
	}
}

void GameScreen::OnKeyReleased(vector< char* > mKeyList)
{
}

/////////////////////////////////MOUSE///////////////////////////

void GameScreen::OnMouseMove(float x, float y)
{
	// Set the 1st Person view
	if(!mGameOver) {
		mPlayer->SetViewByMouse(x, y);
	}
}

////////////////////////////////////////////////////////////////////

/* Load in the trees */
void GameScreen::LoadTrees()
{
	typedef vector< SmartPtr <CVector3> > Vec3List;
	Vec3List mPoints;					// Set up a list of Vectors

	string filename;
	// file path to be accessed to read all the positions from
	filename = "treepos.txt";	
	
	ifstream file(filename.c_str(), ios::in | ios::binary);

	// if file is not empty
	if(file){
		// while the file has not reached the end
		while(!file.eof()){
			float x, z;
			// read in the x and z value
			file >> x >> z;
			// create a new Vector
			SmartPtr<CVector3> vec = new CVector3(x, 0, z);
			// and add it to the list of vectors
			mPoints.push_back(vec);
		}
	}
	// clear the file buffer (Safety reasons)
	file.clear();
	// close the opened file
	file.close();

	for(int i = 0; i < MAX_TREES; i++){
		// Create a new tree
		mTree[i] = new Tree();
		// Obtain the nth  Vector
		CVector3* vec = mPoints[i].GetPtr();
		// Set the Position of the object to the obtained vector from the list
		mTree[i]->SetPosition(*vec);
		mTree[i]->SetGroundValue(0);
		mTree[i]->SetScale(0.5f);
		// Add to the Game World
		mWorld.AddGameObject(mTree[i]);
	}

	mPoints.clear();
}

void GameScreen::LoadCoins()
{
	typedef vector< SmartPtr <CVector3> > Vec3List;
	Vec3List mPoints;

	string filename;
	// file path to be accessed to read all the positions from
	filename = "coinpos.txt";

	ifstream file(filename.c_str(), ios::in | ios::binary);

	// if file is not empty
	if(file){
		// while the file has not reached the end
		while(!file.eof()){
			float x, z;
			// read in the x and z value
			file >> x >> z;
			// create a new Vector
			SmartPtr<CVector3> vec = new CVector3(x, 35, z);
			// and add it to the list of vectors
			mPoints.push_back(vec);
		}
	}
	file.clear();
	file.close();

	for(int i = 0; i < MAX_COINS; i++){
		mCoin[i] = new Coin();
		CVector3* vec = mPoints[i].GetPtr();
		mCoin[i]->SetPosition(*vec);
		mWorld.AddGameObject(mCoin[i]);
		mWorld.AddCollisionEntity(mCoin[i]);
	}

	mPoints.clear();
}

void GameScreen::LoadPowerUps()
{
	typedef vector< SmartPtr <CVector3> > Vec3List;
	Vec3List mPoints;

	string filename;
	// file path to be accessed to read all the positions from
	filename = "powerpos.txt";

	ifstream file(filename.c_str(), ios::in | ios::binary);

	// if file is not empty
	if(file){
		// while the file has not reached the end
		while(!file.eof()){
			float x, z;
			// read in the x and z value
			file >> x >> z;
			// create a new Vector
			SmartPtr<CVector3> vec = new CVector3(x, 35, z);
			// and add it to the list of vectors
			mPoints.push_back(vec);
		}
	}
	file.clear();
	file.close();

	for(int i = 0; i < MAX_POWERUPS; i++){
		// If statement checks if the i value is greater than 1 , which means energy power ups shall be created
		if(i > 1){
			mPowerUp[i] = new PowerUp("powerupenergy");
			CVector3* vec = mPoints[i].GetPtr();
			mPowerUp[i]->SetPosition(*vec);
		}
		else {
			mPowerUp[i] = new PowerUp("poweruphealth");
			CVector3* vec = mPoints[i].GetPtr();
			mPowerUp[i]->SetPosition(*vec);
		}
		mWorld.AddGameObject(mPowerUp[i]);
		mWorld.AddCollisionEntity(mPowerUp[i]);
	}

	mPoints.clear();
}

void GameScreen::LoadEnemies()
{
	typedef vector< SmartPtr <CVector3> > Vec3List;
	Vec3List mPoints;

	string filename;
	// file path to be accessed to read all the positions from
	filename = "enemypos.txt";

	ifstream file(filename.c_str(), ios::in | ios::binary);

	// if file is not empty
	if(file){
		// while the file has not reached the end
		while(!file.eof()){
			float x, z;
			// read in the x and z value
			file >> x >> z;
			// create a new Vector
			SmartPtr<CVector3> vec = new CVector3(x, 24, z);
			// and add it to the list of vectors
			mPoints.push_back(vec);
		}
	}
	file.clear();
	file.close();

	for(int i = 0; i < MAX_ENEMY; i++){
		// If statement checks if the i value is greater than 1 , which means energy power ups shall be created
		mEnemy[i] = new Enemy();
		CVector3* vec = mPoints[i].GetPtr();
		mEnemy[i]->SetPosition(*vec);
		mEnemy[i]->SetWanderStartPositon(*vec);

		mWorld.AddGameObject(mEnemy[i]);
		mWorld.AddCollisionEntity(mEnemy[i]);
		mEnemy[i]->AddListener(&mPlayerManager);
		mEnemy[i]->AddListener(&mScoreKeeper);
		mEnemy[i]->AddListener(&mNotify);
	}

	mPoints.clear();
}