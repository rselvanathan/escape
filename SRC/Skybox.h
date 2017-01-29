#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "GameUtil.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void CreateSkyBox(float x, float y, float z, float width, float height, float length);  //Method to create the skybox
	void CreateSkyboxTextures();  //Method to load the skybox textures
	void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);

	enum{BACK_ID, FRONT_ID, BOTTOM_ID, TOP_ID, LEFT_ID, RIGHT_ID, INTRO_ID};

private:
	UINT g_Texture[MAX_TEXTURES];
};

#endif