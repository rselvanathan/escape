/*
This class just loads all the textures to be used in game. This class makes sure that the textures
are pre loaded only once and can be used in game multiple times. This saves memory and makes the game runs faster

AUthor : Romesh Selvanathan
*/

#include "GameUtil.h"
#include "PreLoader.h"
#include "Model_3DS.h"
#include "GLTexture.h"

PreLoader* PreLoader::mInstance;

PreLoader::PreLoader()
{
	terrain = new GLTexture();
	terrain->Load("Terrain01.bmp");
	crate = new GLTexture();
	crate->Load("crate.bmp");
	heartcrate = new GLTexture();
	heartcrate->Load("heartcrate.bmp");
	energycrate = new GLTexture();
	energycrate->Load("energycrate.bmp");
	score = new GLTexture();
	score->Load("score.bmp");
	switchtex = new GLTexture();
	switchtex->Load("switch.bmp");
	wall = new GLTexture();
	wall->Load("wall.tga");
	particle = new GLTexture();
	particle->Load("Particle.tga");
	smoke = new GLTexture();
	smoke->Load("smoke2.bmp");
	fire = new GLTexture();
	fire->Load("explosion2.bmp");
	intro = new GLTexture();
	intro->Load("intro2.bmp");
}