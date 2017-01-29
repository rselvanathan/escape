#include "Skybox.h"
#include "GameUtil.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{}

void Skybox::CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	AUX_RGBImageRec *pBitmap = NULL;
	FILE *pFile = NULL;									// The File Handle we will use to read the bitmap

	if(!strFileName)									// Return from the function if no file name was passed in
		return;

	pFile = fopen(strFileName,"r");						// Check To See If The File Exists

	if(pFile)											// If we have a valid file pointer we found the file
	{
		pBitmap = auxDIBImageLoad(strFileName);			// Load the bitmap and store the data
	}
	else												// If we can't find the file, quit!
	{													// Prompt the error message
		MessageBox(NULL, "Couldn't find a texture!", "Error!", MB_OK);
		exit(0);
	}

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// This sets the alignment requirements for the start of each pixel row in memory.
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);

	// Lastly, we need to tell OpenGL the quality of our texture map.  GL_LINEAR_MIPMAP_LINEAR
	// is the smoothest.  GL_LINEAR_MIPMAP_NEAREST is faster than GL_LINEAR_MIPMAP_LINEAR, 
	// but looks blochy and pixilated.  Good for slower computers though.  
		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	// The default GL_TEXTURE_WRAP_S and ""_WRAP_T property is GL_REPEAT.
	// We need to turn this to GL_CLAMP_TO_EDGE, otherwise it creates ugly seems
	// in our sky box.  GL_CLAMP_TO_EDGE does not repeat when bound to an object.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture

	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
		{
			free(pBitmap->data);						// Free the texture data, we don't need it anymore
		}

		free(pBitmap);									// Free the bitmap structure
	}
}

void Skybox::CreateSkyboxTextures()
{
	CreateTexture(g_Texture, "nightsky_back.bmp",	BACK_ID		);
	CreateTexture(g_Texture, "nightsky_front.bmp",	FRONT_ID	);
	CreateTexture(g_Texture, "Bottom.bmp",	BOTTOM_ID	);
	CreateTexture(g_Texture, "nightsky_top.bmp",		TOP_ID		);
	CreateTexture(g_Texture, "nightsky_right.bmp",	LEFT_ID		);
	CreateTexture(g_Texture, "nightsky_left.bmp",	RIGHT_ID	);
	CreateTexture(g_Texture, "Intro.bmp",	INTRO_ID	);
}

void Skybox::CreateSkyBox(float x, float y, float z, float width, float height, float length)
{
	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, g_Texture[BACK_ID]);

	// This centers the sky box around (x, y, z)
	x = x - width  / 2;
	y = (y - height / 2) + 75;
	z = z - length / 2;

	 glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////BACK SIDE
		// Start drawing the side as a QUAD
	 glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the BACK Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z);
		
	glEnd();

	// Bind the FRONT texture of the sky map to the FRONT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[FRONT_ID]);

	glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////FRONT SIDE
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);	
	
		// Assign the texture coordinates and vertices for the FRONT Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z + length);
	glEnd();

	// Bind the BOTTOM texture of the sky map to the BOTTOM side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[BOTTOM_ID]);

	glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////BOTTOM SIDE
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
	
		// Assign the texture coordinates and vertices for the BOTTOM Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();

	// Bind the TOP texture of the sky map to the TOP side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[TOP_ID]);
	
	glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////TOP SIDE
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the TOP Side
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);
		
	glEnd();

	// Bind the LEFT texture of the sky map to the LEFT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[LEFT_ID]);
	
	glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////LEFT SIDE
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the LEFT Side
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);		
		
	glEnd();

	// Bind the RIGHT texture of the sky map to the RIGHT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[RIGHT_ID]);

	glNormal3f(0.0f, 0.0f, 1.0f);///////////////////////////////////////////////////////////////////////////////////////////////RIGHT SIDE
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		

		// Assign the texture coordinates and vertices for the RIGHT Side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
	glEnd();
}