/*
This Class sets up the game session by initialising the opengl window, the frame timer and the input.
It also manages the different screens

Author : Romesh Selvanathan
*/

#include "GameSession.h"
#include "GameUtil.h"
#include "GLWindow.h"
#include "FrameTimer.h"
#include "InputManager.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Graphics.h"

/* Destructor */ 
GameSession::~GameSession()
{
	SAFE_DELETE(p_Fps);
	SAFE_DELETE(menu);
	SAFE_DELETE(game);
	SAFE_DELETE(gameOver);
	SAFE_DELETE(mInput);
}

/* Initialise the OpenGl Window as well as frame timer and the input */ 
bool GameSession::Init(HINSTANCE hInstance, bool fullscreenflag)
{
	// If OpenGlWindow has not been initialised 
	if(!GLWindow::GetInstance()->Init(hInstance, fullscreenflag))
		// Kill the OpenGl window
		GLWindow::GetInstance()->KillGLWindow();

	// Set up a new Frame Timer
	p_Fps = new FrameTimer();
	// Set its frames per sceond to 60 and initlaise the consistent frame time
	p_Fps->init(60);

	// Initialize the Input
	mInput = new InputManager();

	// Create a new menu and gameover screen
	// NOTE: game screen is not here as when the restarts it caused errors so had to move it
	menu = new MenuScreen();
	gameOver = new GameOverScreen();

	menu->SetInput(mInput.GetPtr());

	// Set the current state
	mScreenState = MENU;

	// initialisation went ok
	return true;
}

/* Update the game */ 
void GameSession::Update(float dt)
{
	// Switch the state of the current screen
	switch (mScreenState){
		case MENU : menu->Update(dt);
					// if state should switch
					if(menu->GetStateSwitch()) {
						// change to game state
						mScreenState = GAME; 
						// Seemed to cause an issue when i Created the object in Init method for some reason
						// where everytime the game was restarted the game would start speeding up for a bizarre reason
						// so I recreate the whole object again when game is restarted and it seemed to be perfectly fine
						// I Checked all the speed values for camera movement speed with debug window - no clue why it went faster
						game = new GameScreen();
						// Obtain the difficulty chosen 
						game->Init(menu->GetDifficultyState());
						game->SetInput(mInput.GetPtr());
					}
					break;
		case GAME : game->Update(dt); 
					// if state should switch
					if(game->GetStateSwitch()) {
						// change to game over state
						mScreenState = GAMEOVER;
						gameOver->Reset();
						gameOver->SetScore(game->GetScore());
						gameOver->SetInput(mInput.GetPtr());
					}break;
		case GAMEOVER: gameOver->Update(dt);
						// if state should switch
						if(gameOver->GetStateSwitch()){
							// change to game over state
							mScreenState = GAME;
							game = new GameScreen();
							// Obtain the difficulty chosen 
							game->Init(menu->GetDifficultyState());
							game->SetInput(mInput.GetPtr());
						}
						break;
	}
}

/* Render the game to the screen */ 
void GameSession::Render()
{
	// Clear and Reset the Screen
	Graphics::GetInstance()->ClearScreen();

	// Switch the screen depending on state
	switch (mScreenState){
		case MENU : menu->Render(); break;
		case GAME : game->Render(); break;
		case GAMEOVER : gameOver->Render(); break;
	}
}

/* The Main Loop */ 
WPARAM GameSession::MainLoop()
{
	MSG msg;

	while(1)											// Do our infinate loop
	{													// Check if there was a message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        { 
			if(msg.message == WM_QUIT)					// If the message wasnt to quit
				break;
            TranslateMessage(&msg);						// Find out what the message does
            DispatchMessage(&msg);						// Execute the message
        }
		else											// if there wasn't a message
		{ 
			// Do computationally expensive things here.  We want to render the scene
			// every frame, so we call our rendering function here.  Even though the scene
			// doesn't change, it will bottle neck the message queue if we don't do something.
			// Usually WaitMessage() is used to make sure the app doesn't eat up the CPU.

			// Get the elapsed time since last update
			float dt = p_Fps->GetElapsedTimeSinceLastUpdate()/1000;
			if(dt > 7)
				dt = 7;

			// Update the Different Input 
			mInput->OnMouseMove();
			mInput->OnKeyPressed();
			mInput->OnKeyPressRelease(); 

			Update(dt);
			Render();

			// Swap the buffers to render the scene
			SwapBuffers(GLWindow::GetInstance()->GetHDC());	
        } 
	}

	// Kill the Window
	GLWindow::GetInstance()->KillGLWindow();
	return(msg.wParam);									// Return from the program
}
