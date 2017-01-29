/*
This class handles all the input. So basically whatever key has been pressed will be put inside a list
of keys that were pressed and sent to all its listeners. This makes sure that when an error in input occurs 
the game will still carry on without crashing .

Author : Romesh Selvanathan
*/

#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "GameUtil.h"
#include "IKeyboardListener.h"
#include "IMouseListener.h"

class InputManager
{
public :
	InputManager();
	~InputManager(){}

	////////////////////////////MOUSE//////////////////////////////////////////////
	void OnMouseMove();
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////KEYBOARD////////////////////////////////////////////
	void OnKeyPressed();
	void OnKeyReleased();
	void OnKeyPressRelease();

	bool KeyDown(SHORT key);
	bool KeyUp(SHORT key);
	bool KeyDownAndUp(SHORT key);
	////////////////////////////////////////////////////////////////////////////////

	void AddKeyboardListener(SmartPtr<IKeyboardListener> lptr){mKeyboardListeners.push_back(lptr);}
	void RemoveKeyboardListener(SmartPtr<IKeyboardListener> lptr){mKeyboardListeners.remove(lptr);}
	list< SmartPtr<IKeyboardListener> > GetKeyboardListeners(){return mKeyboardListeners;}

	void AddMouseListener(SmartPtr<IMouseListener> lptr){mMouseListeners.push_back(lptr);}
	void RemoveMouseListener(SmartPtr<IMouseListener> lptr){mMouseListeners.remove(lptr);}
	list< SmartPtr<IMouseListener> > GetMouseListeners(){return mMouseListeners;}
private:
	typedef list< SmartPtr<IKeyboardListener> > KeyboardListenerList;
	KeyboardListenerList mKeyboardListeners;

	typedef list< SmartPtr<IMouseListener> > MouseListenerList;
	MouseListenerList mMouseListeners;

	typedef vector< char* > mKeyList;
	mKeyList key;

	typedef vector<char*> mKeyReleaseList;
	mKeyReleaseList keyRelease;

	char* keyPressRelease;							// char representaton of the current key pressed
	bool wKeyPrev, sKeyPrev, ReturnKeyPrev;			// previous states of w, s, and return keys (QUIK EASY)
};

#endif