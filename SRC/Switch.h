/*
There are a number of switches in the game world which will have to be activated in order to enter a portal

Author : Romesh Selvanathan
*/ 

#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "ISwitchListener.h"
#include "GLBox.h"

class Switch : public GameObject
{
public :
	/* Constructor */
	Switch(const char* name);
	/* Destructor */ 
	virtual ~Switch();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	virtual void Update(float dt);
	virtual void Render();
	virtual bool CollisionTest(Entity* o);
	virtual void OnCollision(Entity* o);
	////////////////////////////////////////////////////////////////////////////////////////////////////

	// Listeners for the switch
	void AddListener(SmartPtr<ISwitchListener> lptr) {mListeners.push_back(lptr);}
	// Fire messages to its listeners
	void FireSwitchTurned()
	{
		for(SwitchListeners::iterator it = mListeners.begin(); it != mListeners.end(); it++)
			(*it)->OnSwitchTurned(blue, red);
	}
	void FireSwitch2Turned()
	{
		for(SwitchListeners::iterator it = mListeners.begin(); it != mListeners.end(); it++)
			(*it)->OnSwitchTurned2(blue2, red2, yellow2);
	}

private:
	bool red, blue;					// The first set of switches
	bool red2, blue2, yellow2;		// The second set of switches

	GLBox box;						// A 3D openGl box

	typedef list<SmartPtr<ISwitchListener>> SwitchListeners;
	SwitchListeners mListeners;		// Listeners to this object
};


#endif 