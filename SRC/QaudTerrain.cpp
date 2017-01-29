#include "QuadTerrain.h"
#include "GameUtil.h"
#include "GLTexture.h"
#include "PreLoader.h"


QuadTerrain::QuadTerrain(float scale, CVector3 position)
{
	height = TERRAIN_SIZE/200.0f;
	width = TERRAIN_SIZE/200.0f;
	
	//centre texture around 0,0,0;
	x = -width  / 2;
	y = u = v = 0;
	z = -height / 2;
}

QuadTerrain::~QuadTerrain()
{
}

void QuadTerrain::RenderQuadTerrain()
{
	// Bind and use the texture
	glPushMatrix();
		PreLoader::GetInstance()->terrain->Use();
		glColor4f(0.5, 0.5, 0.5, 1);
		for ( int i = -50; i < 50; i+= 1) {
			for(int j = -50; j < 50; j += 1) {
				glNormal3f(0.0f, 1.0f, 0.0f);///////////////////////////////////////////////////////////////////////////////////////////////BOTTOM SIDE
				// Start drawing the side as a QUAD
				glBegin(GL_QUADS);		
	
				// Assign the texture coordinates and vertices for the BOTTOM Side
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x + x*i*2,	y,	z+x*j*2);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x + x*i*2,	y,	z + height+x*j*2);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width + x*i*2, y, z + height+x*j*2); 
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width + x*i*2, y, z+x*j*2);
				glEnd();
			}
		}  

	glPopMatrix();

	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}

