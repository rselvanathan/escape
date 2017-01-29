/*
A class that represents a menu entry in any of the menu like screens. These menus will scale
in size or have other effects(change in color over time etc ...)

Author : Romesh Selvanathan
*/

#ifndef __MENUENTRY_H__
#define __MENUENTRY_H__

#include "GameUtil.h"
class GL2DText;

class MenuEntry
{
public:
	/* Constructor */
	MenuEntry(char* text);
	/* Destructor */
	~MenuEntry();

	/* Update this object */
	void Update(bool isSelected, int dt);
	/* Render this object onto the scren */
	void Render(float xPosition, float yPosition);

	/* Return the text to be printed on screen */ 
	const char* GetText() const {return mPrint;}

private:
	SmartPtr<GL2DText> mText;	 // pointer to the GL2Dtext class

	char* mPrint;				 // the text to be printed
	float r, g, b, a;			 // red, green, blue, alpha components

	float mSelectionFade;		 // for pulsating the font
	float pulsate;				 // the pulsate variable
	float cnt1, cnt2;			 // There to cause some random effects on color and position
	float random;				 // Same as above used in Raster2F()
};

#endif