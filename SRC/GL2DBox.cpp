/*
This class simply creates a opengl 2D box in orthogonal view to be used in things like the HUD

Author : Romesh Selvanathan
*/

#include "GL2DBox.h"
#include "GameUtil.h"
#include "Graphics.h"

/* Constructor */
GL2DBox::GL2DBox()
{
	/* Initialise the values */
	x = y = width = height = 0.0f;
	scale = r = g = b = a = 1.0f;
	texture = NULL;
}

/* Destructor */
GL2DBox::~GL2DBox()
{}

/* Initialise the width, height, xPosition and YPosition of the box */
void GL2DBox::Init(float Width, float Height, float X, float Y)
{
	width = Width;
	height = Height;
	x = X;
	y = Y;
}
/* Set the Position of this box */
void GL2DBox::SetPosition(float X, float Y)
{x = X; y = Y;}

/* Set the Color of this box, including the alpha channel */
void GL2DBox::SetColor(float _r, float _g, float _b, float _a)
{r = _r; g = _g; b = _b; a = _a;}

/* Set the scale of this box */
void GL2DBox::SetScale(float Scale)
{scale = Scale;}

/* Set The texture to be used by this box */ 
void GL2DBox::SetTexture(unsigned int Texture)
{texture = Texture;}

/* Set the width of this box */
void GL2DBox::SetWidth(float Width)
{width = Width;}

/* Render the box */
void GL2DBox::Render()
{
	// Disable Lighting and GL2DTexturing (for now)
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// Set Up Orthographic View
	Graphics::GetInstance()->SetOrthoView(0, 800, 0, 600);
	// Store current Matrix
	Graphics::GetInstance()->StoreMatrix();

	// If a texture is specifed enable 2D texture 
	if(texture != NULL)
		glEnable(GL_TEXTURE_2D);

	// Translate, Color and scale the 2D box
	Graphics::GetInstance()->Translate(x, y, 0);
	Graphics::GetInstance()->Color4(r, g, b, a);
	Graphics::GetInstance()->Scale(scale);

	// If a texture is specified Bind the texture to this box
	if(texture !=NULL)
		Graphics::GetInstance()->Bind2DTexture(texture);

	// Begin Drawing the 2D box
	if(texture !=NULL)
		Graphics::GetInstance()->Draw2DQuad(0, width, -height, height, 0, 1, 0, 1);
	else
		Graphics::GetInstance()->DrawQuad(width, height, 0);

	// If a texture is specified disable the texture
	if(texture !=NULL)
		glDisable(GL_TEXTURE_2D);

	//Release Current Matrix
	Graphics::GetInstance()->ReleaseMatrix();
	Graphics::GetInstance()->SetPerspective();
	// Reset back to Perspective

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}