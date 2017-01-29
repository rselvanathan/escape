/*
This Class sets up the game session by initialising the opengl window, the frame timer and the input.
It also manages the different screens

Author : Romesh Selvanathan
*/ 
#ifndef __GAMESESSION_H__
#define __GAMESESSION_H__

#include "GameUtil.h"

class FrameTimer;
class InputManager;
class MenuScreen;
class GameScreen;
class GameOverScreen;

class GameSession
{
public:
	/* Constructor */
	GameSession(){};
	/* Destructor */ 
	~GameSession();

	/* Initialise the OpenGl Window as well as frame timer and the input */ 
	bool Init(HINSTANCE hInstance, bool fullscreenflag);

	/* Update the game */ 
	void Update(float dt);
	/* Render the game to the screen */ 
	void Render();

	/* The Main Loop */ 
	WPARAM MainLoop();

private:
	SmartPtr<FrameTimer> p_Fps;					// Pointer to the frame timer
	SmartPtr<MenuScreen> menu;					// Pointer to menu Screen
	GameScreen* game;							// Pointer to the main game screen
	SmartPtr<GameOverScreen> gameOver;			// Pointer to the game over screen
	SmartPtr<InputManager> mInput;				// Pointer to Input manager

	enum{MENU, GAME, GAMEOVER};					// Different screen states
	int mScreenState;							// the current screen state
};

#endif