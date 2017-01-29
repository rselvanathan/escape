/*
This class sets up the gameover screen at the end when the game is finished. It has two sets of choices
Restart and Quit. Depending on the choice the game will either restart back to the menu screen or quite all
together. It also shows the score obtained last by the player

Author : Romesh Selvanathan
*/

#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H__

#include "GameUtil.h"
#include "IKeyboardListener.h"
#include "InputManager.h"

class MenuEntry;
class InputManager;
class GL2DText;
class GLText;

class GameOverScreen : public IKeyboardListener
{
public:
	/* Construstor */
	GameOverScreen();
	/* Destructor */
	~GameOverScreen();

	/* Reset this object */
	void Reset();
	/* Update this object */
	void Update(float dt);
	/* Render this object onto the scren */
	void Render();

	/////////////////////////////////////////////IKEYBOARDLISTENER//////////////
	virtual void OnKeyPressed(vector< char* > mKeyList){}
	virtual void OnKeyReleased(vector< char* > mKeyList){}
	virtual void OnKeyPressAndRelease(char* key);
	////////////////////////////////////////////////////////////////////////////

	/* Return if the switching of screen state should occur */
	const bool GetStateSwitch() const {return mStateSwitch;}
	/* Return the difficulty chosen by the player */
	void SetScore(int v) {currentScore = v;}

	// Turn this screen into a keyboard listener
	void SetInput(InputManager* mInput) {mInput->AddKeyboardListener(this);}

	/* the 2 choice states */
	enum {RESTART, QUIT};
private:
	typedef vector<SmartPtr<MenuEntry>> MenuEntryList;
	MenuEntryList menuEntries;				// List of menu entries

	int selectedEntry;						// The selected menu entry
	void OnSelected(int selected);			// Method for when a menu entry has been selected

	SmartPtr<GL2DText> title;				// Title of the screen
	SmartPtr<GLText> score;					// Score text to be shown on screen 
	int currentScore;						// Title of the screen
		
	bool mStateSwitch;						// should the state switch occur
};

#endif