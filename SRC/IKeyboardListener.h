#ifndef __IKEYBOARDLISTENER__
#define __IKEYBOARDLISTENER__

#include <list>

class IKeyboardListener
{
public:
	virtual void OnKeyPressed(vector< char* > mKeyList) = 0;
	virtual void OnKeyReleased(vector< char* > mKeyList) = 0;
	virtual void OnKeyPressAndRelease(char* key) = 0;
};

#endif 