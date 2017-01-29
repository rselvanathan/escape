#include "MenuEntry.h"
#include "GameOverScreen.h"
#include "GameUtil.h"
#include "InputManager.h"
#include "GL2DText.h"
#include "GLText.h"
#include "Graphics.h"

/* Constructor */
GameOverScreen::GameOverScreen()
{
	// Initialise values
	selectedEntry = 0;
	mStateSwitch = false;

	// Add onto the list the two new Menu Entries
	if(menuEntries.empty()){
		menuEntries.push_back(new MenuEntry("Restart"));
		menuEntries.push_back(new MenuEntry("Quit"));
	}

	// Initialise a title to the screen
	title = new GL2DText();
	title->SetPosition(CVector3(250, 500, 0));
	title->glSetColor(1.0, 0, 0.0, 1);
	title->SetScale(2);

	// Initialise a score text to the screen
	score = new GLText();
	score->CreateText(-20, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS,
					CLIP_DEFAULT_PRECIS, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
	score->SetColor3f(1, 1, 1);
	score->SetPosition(300, 350);
}

/* Destructor */ 
GameOverScreen::~GameOverScreen()
{
	// If the list of menu entries is not empty clear the list
	if(!menuEntries.empty())
		menuEntries.clear();
}

/* Reset this object */
void GameOverScreen::Reset()
{
	selectedEntry = 0;
	mStateSwitch = false;
}

/* Do the required action depending on which menu item has been chosen */ 
void GameOverScreen::OnSelected(int selectEntry)
{
	if(selectEntry == 0) {
		mStateSwitch = true; 
	}
	if(selectEntry == 1){
		PostQuitMessage(0);
	}
}

/* Update the screen */
void GameOverScreen::Update(float dt)
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
void GameOverScreen::Render()
{
	// y Position for each menu entry
	float y = 250.f;
	Graphics::GetInstance()->ResetMatrix();
	
	Graphics::GetInstance()->StoreMatrix();
	// iterate through each menu entry 
	for(MenuEntryList::iterator it = menuEntries.begin(); it != menuEntries.end(); ++it)
	{
		// poisiton each mnu entry at x = 100 and at different y levels
		(*it) ->Render(350, y);
		y -= 50;
	}
	Graphics::GetInstance()->ReleaseMatrix();

	title->glPrint(" GAME OVER ", GL2DText::ITALIC);
	score->print(" Score : %i " , currentScore);
}

/* Actions according to each key press */ 
void GameOverScreen::OnKeyPressAndRelease(char* key)
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
