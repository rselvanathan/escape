/*
This class sets up the intro/menu screen at the beginning when the game is started. It has two sets of choices
EASY and HARD. Depending on the choice the time left on the game itself is changed

Author : Romesh Selvanathan
*/
#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "GameUtil.h"
#include "IKeyboardListener.h"
#include "InputManager.h"
#include "GL2DBox.h"

class MenuEntry;
class InputManager;

class MenuScreen : public IKeyboardListener
{
public:
	/* Constructor */
	MenuScreen();
	/* Destructor */
	~MenuScreen();

	/* Reset this object */
	void Reset();
	/* Update this object */
	void Update(float dt);
	/* Render this object onto the scren */
	void Render();

	/////////////////////////////////////////////IKEYBOARDLISTENER////////////////////////////////////
	virtual void OnKeyPressed(vector< char* > mKeyList){}
	virtual void OnKeyReleased(vector< char* > mKeyList){}
	virtual void OnKeyPressAndRelease(char* key);
	//////////////////////////////////////////////////////////////////////////////////////////////////

	/* Return if the switching of screen state should occur */
	const bool GetStateSwitch() const {return mStateSwitch;}
	/* Return the difficulty chosen by the player */
	const int GetDifficultyState() const {return mDifficultyState;}

	// Turn this screen into a keyboard listener
	void SetInput(InputManager* mInput) {mInput->AddKeyboardListener(this);}

	/* the 2 diffuclty states */
	enum {EASY, HARD};
private:
	typedef vector<SmartPtr<MenuEntry>> MenuEntryList;
	MenuEntryList menuEntries;			// List of menu entries

	int selectedEntry;					// The selected menu entry
	void OnSelected(int selected);		// Method for when a menu entry has been selected

	bool mStateSwitch;					// should the state switch occur
	int mDifficultyState;				// the chosen difficulty state

	GL2DBox box;
};

#endif