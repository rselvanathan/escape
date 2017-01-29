/*
A class that represents a menu entry in any of the menu like screens. These menus will scale
in size or have other effects(change in color over time etc ...)

Author : Romesh Selvanathan
*/


#include "GameUtil.h"
#include "MenuEntry.h"
#include "GL2DText.h"

/* Constructor */
MenuEntry::MenuEntry(char* text) : mPrint(text), r(0), g(0), b(0) ,a(1.0f) , 
	cnt1(0), cnt2(0), random(1.0f/1000.0f), pulsate(1.f), mText(new GL2DText()), mSelectionFade(0)
{
}

/* Destructor */
MenuEntry::~MenuEntry()
{
	SAFE_DELETE(mText);
	SAFE_DELETE(mPrint);
}

/* Update this object */
void MenuEntry::Update(bool isSelected, int dt)
{
	// a fade speed value
	float fadeSpeed = 0;
	// obtain a new fade speed value as time goes on by adding to the current fading speed
	fadeSpeed += (float)(dt * 20) / 1000;

	/* If this text is selected */ 
	if(isSelected)
	{
		// add the fadespeed to the current selection fade
		float temp = mSelectionFade + fadeSpeed;
		// if it is greater than one then limit it to 1
		if(temp >= 1)
			mSelectionFade = 1;
		else 
			// otherwise = to temp
			mSelectionFade = temp;

		// Change the color of the text (Creates a rainbo wlike effect)
		r = 1.0f * float(cos(cnt1));
		g = 1.0f * float(sin(cnt2));
		b = 1.0f - 0.5f * float(cos(cnt1));
	}
	else
	{
		// if it is not selected then reduce the fading back to normal alpha value again
		float temp = mSelectionFade - fadeSpeed;
		if(temp <= 0)
			mSelectionFade = 0;
		else
			mSelectionFade = temp;

		// Set the Colors back to white
		r = b = g = 1.0f;
		a = 1.0f;
	} 

	// Pulsate the text within a certain range of values
	pulsate = 1-0.1f* float(cos(cnt1)) * mSelectionFade;

	cnt1 +=0.051f * dt;
	cnt2 +=0.005f * dt;
}

/* Render this object onto the scren */
void MenuEntry::Render(float xPosition, float yPosition)
{
	mText->SetPosition(CVector3(xPosition, yPosition, 0));
	mText->glSetColor(r, g, b, a);
	mText->glPrint(mPrint, 0);
}