/*
This class simply creates a opengl 2D box in orthogonal view to be used in things like the HUD

Author : Romesh Selvanathan
*/

#ifndef __GL2DBOX_H__
#define __GL2DBOX_H__

class GL2DBox
{
public:
	/* Constructor */
	GL2DBox();

	/* Destructor */
	~GL2DBox();

	/* Initialise the width height and length of the box */
	void Init(float Width, float Height, float X, float Y);
	/* Set The texture to be used by this box */ 
	void SetTexture(unsigned int Texture);
	/* Set the Position of this box */
	void SetPosition(float X, float Y);
	/* Set the Color of this box, including the alpha channel */
	void SetColor(float _r, float _g, float _b, float _a);
	/* Set the scale of this box */
	void SetScale(float Scale);
	/* Set the width and height of the ball */
	void SetWidth(float Width);
	/* Render the box */
	void Render();
private:
	float width, height;			// width and height of the box
	float x, y;						// x and y position of the box
	float r, g, b, a;				// the 3 color components as well as the alpha value
	float scale;					// scale of the box
	unsigned int texture;			// the texture assigned to the box
};


#endif