/*
This class handles all the input. So basically whatever key has been pressed will be put inside a list
of keys that were pressed and sent to all its listeners. This makes sure that when an error in input occurs 
the game will still carry on without crashing .

Author : Romesh Selvanathan
*/

#include "InputManager.h"
#include "GameUtil.h"

/* Constructor */  
InputManager::InputManager()
{
	wKeyPrev = sKeyPrev = ReturnKeyPrev = false;
}

void InputManager::OnMouseMove()
{
	// This is a window structure that holds an X and Y
	POINT mousePos;	
	// This is a binary shift to get half the width
	int middleX = SCREEN_WIDTH  >> 1;	
	// This is a binary shift to get half the height
	int middleY = SCREEN_HEIGHT >> 1;		
	// Get the mouse's current X,Y position
	GetCursorPos(&mousePos);					
	// If our cursor is still in the middle, we never moved... so don't update the screen
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;
	// Set the mouse position to the middle of our window
	SetCursorPos(middleX, middleY);	
	// Get the Direction the mouse moved in
	float x = (float)( (middleX - mousePos.x) );
	float y = (float)( (middleY - mousePos.y) );

	for(MouseListenerList::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); it++)
	{
		(*it)->OnMouseMove(x, y);
	}
}

/* Checks whether the specifed keys have been pressed then 
   sends a vector of keys to its listeners(for multiple key presses at once)*/ 
void InputManager::OnKeyPressed()
{
	// Check if we hit the Up arrow or the 'w' key
	if(GetKeyState('W') & 0x80) {				

		//key = "W";
		key.push_back("W");
	} 
	
	// Check if we hit the Down arrow or the 's' key
	if(GetKeyState('S') & 0x80) {			

		//key = "S";	
		key.push_back("S");
	}

	// Check if we hit the Left arrow or the 'a' key
	if(GetKeyState('A') & 0x80) {			

		//key = "A";
		key.push_back("A");
	}

	// Check if we hit the Right arrow or the 'd' key
	if(GetKeyState('D') & 0x80) {			

		//key = "D";
		key.push_back("D");
	}	

	if(GetKeyState('Q') & 0x80) {			

		//key = "D";
		key.push_back("Q");
	}	

	if(GetKeyState('E') & 0x80) {
		key.push_back("E");
	}

	if(GetKeyState('C') & 0x80) {
		key.push_back("C");
	}

	// Iterate through each keyboard listener and pass the vector of keys
	for(KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); it++)
	{
		(*it)->OnKeyPressed(key); 
	}
	// reset key values
	key.clear();
}

void InputManager::OnKeyReleased()
{
	
	// Check if we hit the Up arrow or the 'w' key
	if(GetKeyState('W') & 0x80) {} 
	else
	{
		keyRelease.push_back("W");
	}
		// Check if we hit the Down arrow or the 's' key
	if(GetKeyState('S') & 0x80) {}			

		//key = "S";	
	else{
		keyRelease.push_back("S");
	}

	// Check if we hit the Left arrow or the 'a' key
	if(GetKeyState('A') & 0x80) {}			

		//key = "A";
	else{
		keyRelease.push_back("A");
	}

	// Check if we hit the Right arrow or the 'd' key
	if(GetKeyState('D') & 0x80) {}			

		//key = "D";
	else{
		keyRelease.push_back("D");
	}	
	
	for(KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); it++)
	{
		(*it)->OnKeyReleased(keyRelease); 
	}
	// reset key values
	keyRelease.clear();
}

void InputManager::OnKeyPressRelease()
{
	// Check if "W" has been pressed
	bool keyW = GetKeyState('W') < 0;
	// the w has been pressed and released
	if((keyW) && (!wKeyPrev))
		// store the "W" in the char* representation
		keyPressRelease = "W";
	// previous state = current state
	wKeyPrev = keyW;

	// same as above
	bool keyS = GetKeyState('S') < 0;
	if((keyS) && (!sKeyPrev))
		keyPressRelease = "S";
	sKeyPrev = keyS;

	// same as above
	bool keyReturn = GetKeyState(VK_RETURN) < 0;
	if((keyReturn) && (!ReturnKeyPrev))
		keyPressRelease = "VK_RETURN";
	ReturnKeyPrev = keyReturn;


	for(KeyboardListenerList::iterator it = mKeyboardListeners.begin(); it != mKeyboardListeners.end(); it++)
	{
		(*it)->OnKeyPressAndRelease(keyPressRelease); 
	}
	keyPressRelease = "";
}

//////////////////////////////////////////////// Testing ///////////////////////////////////////////////
bool InputManager::KeyDown(SHORT key)
{
	if(GetAsyncKeyState(key))// & 0x80)
		return true;
	else
		return false;
}

bool InputManager::KeyUp(SHORT key)
{
	if(GetAsyncKeyState(key))
		return false;
	else
		return true;
}

bool InputManager::KeyDownAndUp(SHORT key)
{
	/*char * test = "false";
    float i = 0;
	if(KeyDown(key)){
		down = true;
		//test = "true";
		//i = 1;
	}
	if(down){
		if(KeyUp(key)){
			up = true;
			test = "true";
			i = 2;
		}
	}
	printf("%s \n", test);
	if(up){
		down = false;
		up = false;
		return true;
	}
	else*/ 
		return false; 
} 

