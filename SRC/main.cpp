#include "GameUtil.h"
#include "GameSession.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>

bool fullscreen;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow)
{	
	GameSession* game;
	game = new GameSession();

	// Check if we want full screen or not
	if(MessageBox(NULL, "Click Yes to go to windowed mode", "Options", MB_YESNO | MB_ICONQUESTION) == IDNO)
		fullscreen = TRUE;


	if(!game->Init(hInstance, fullscreen)){
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;	
	 }

	// Run our message loop and after it's done, return the result	
	if( game != NULL)
		return game->MainLoop();
	else{
		SAFE_DELETE(game);	
		return 0;
	}
}