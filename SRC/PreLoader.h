/*
This class just loads all the textures to be used in game. This class makes sure that the textures
are pre loaded only once and can be used in game multiple times. This saves memory and makes the game runs faster

AUthor : Romesh Selvanathan
*/
#ifndef __PRELOADER_H__
#define __PRELOADER_H__

#include "GameUtil.h"
class GLTexture;

class PreLoader
{
public:
	// Create A instance of this Preloader class
	static PreLoader* GetInstance()
	{
		if(mInstance == NULL)
			mInstance = new PreLoader();
		return mInstance;
	}
	// All the textures to be loaded are public and can be accessed by any class
	SmartPtr<GLTexture> terrain;
	SmartPtr<GLTexture> crate;
	SmartPtr<GLTexture> heartcrate;
	SmartPtr<GLTexture> energycrate;
	SmartPtr<GLTexture> score;
	SmartPtr<GLTexture> switchtex;
	SmartPtr<GLTexture> wall;
	SmartPtr<GLTexture> particle;
	SmartPtr<GLTexture> smoke;
	SmartPtr<GLTexture> fire;
	SmartPtr<GLTexture> intro;

private:
	PreLoader();
	static PreLoader* mInstance;
};

#endif