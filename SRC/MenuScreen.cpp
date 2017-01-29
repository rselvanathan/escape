#include "MenuEntry.h"
#include "MenuScreen.h"
#include "GameUtil.h"
#include "InputManager.h"
#include "Graphics.h"
#include "GL2DBox.h"
#include "PreLoader.h"
#include "GLTexture.h"

/* Constructor */
MenuScreen::MenuScreen()
{
	// Initialise values
	selectedEntry = 0;
	mDifficultyState = 0;
	mStateSwitch = false;

	// Add onto the list the two new Menu Entries
	if(menuEntries.empty()){
		menuEntries.push_back(new MenuEntry("EASY"));
		menuEntries.push_back(new MenuEntry("HARD"));
	}

	// Set up the 2D box an apply the texture on it
	box.Init(800, 300, 0, 300);
	box.SetTexture(PreLoader::GetInstance()->intro->texture[0]);
}

/* Destructor */ 
MenuScreen::~MenuScreen()
{
	// If the list of menu entries is not empty clear the list
	if(!menuEntries.empty())
		menuEntries.clear();
}

/* Reset this object */
void MenuScreen::Reset()
{
	selectedEntry = 0;
	mDifficultyState = 0;
	mStateSwitch = false;
}

/* Do the required action depending on which menu item has been chosen */ 
void MenuScreen::OnSelected(int selectEntry)
{
	if(selectEntry == 0) {
		mStateSwitch = true; 
		mDifficultyState = EASY;
	}
	if(selectEntry == 1){
		mStateSwitch = true; 
		mDifficultyState = HARD;
	}
}

/* Update the screen */
void MenuScreen::Update(float dt)
{
	// iterate thorugh each menu entry and update them accordingly
	for(int i = 0; i < menuEntries.size(); i++)
	{	
		// is the current selectedEntry equal to current menuEntry[i]
		bool isSelected = (i == selectedEntry);
		menuEntries[i]->Update(isSelected, dt);
	}
}

/* Render the Menu Screen */ 
void MenuScreen::Render()
{
	// y Position for each menu entry
	float y = 300.f;
	Graphics::GetInstance()->ResetMatrix();

	// Render the 2D box
	box.Render();

	Graphics::GetInstance()->StoreMatrix();
	// iterate through each menu entry 
	for(MenuEntryList::iterator it = menuEntries.begin(); it != menuEntries.end(); ++it)
	{
		// poisiton each mnu entry at x = 100 and at different y levels
		(*it) ->Render(370, y);
		y -= 50;
	}
	Graphics::GetInstance()->ReleaseMatrix();
}

/* Actions according to each key press */ 
void MenuScreen::OnKeyPressAndRelease(char* key)
{
	if(key == "W"){
			// Move up the menu entries
			selectedEntry--;
			// is the entry is < 0 reset it to the bottom
			if(selectedEntry < 0)
				selectedEntry = menuEntries.size() - 1;	
		}
		if(key == "S"){
			// Move down the entries
			selectedEntry++;
			// if entry is greater than number if items in the vector
			// reset back to the top
			if(selectedEntry >= menuEntries.size())
				selectedEntry = 0;
		}
		if(key == "VK_RETURN")
			OnSelected(selectedEntry);
}
