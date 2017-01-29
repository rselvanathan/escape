#ifndef __QUADTERRAIN_H__
#define __QUADTERRAIN_H__

#include "GameUtil.h"

class GLTexture;

#define TERRAIN_SIZE		10000				// This is the size of our terrain */ 

class QuadTerrain{
public:
	QuadTerrain(float scale, CVector3 position);
	~QuadTerrain();

	void RenderQuadTerrain();

private:
	float x, y, z, u, v; //width, height;
	int	width, height;								// Hold width and height of the heightmap
};

#endif