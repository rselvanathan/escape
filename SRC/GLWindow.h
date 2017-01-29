/* 
This class creates OpenGL Window. This class is a singleton to make sure only one window is created
at any time.

Author : Romesh Selvanathan
*/

#ifndef __GLWINDOW_H__
#define __GLWINDOW_H__

#include "GameUtil.h"

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

class GLWindow
{
public:
	/* Obtain a Single Instance of this Window */ 
	static GLWindow* GetInstance()
	{
		if(!mInstance)
			mInstance = new GLWindow();
		return mInstance;
	}
	/* Destructor */
	~GLWindow();
	
	/* Initialise the Window */
	bool Init(HINSTANCE hInstance, bool fullscreenFlag);

	/* Create a Window */
	HWND CreateWindowGL(const char* title, int width, int height, int bits, bool fullscreenflag, HINSTANCE hInstance);

	/* Initialise OpenglWindow */
	void InitOpenGL(int width, int height);
	/* Setup the Pixel Format for the Window */ 
	bool bSetupPixelFormat();
	/* Kill the Window */
	void KillGLWindow();
	/* Change the window to fullscreen */
	void ChangeToFullscreen(int width, int height, int pixels);
	/* When window is resized, resize the opengl window aswel */
	GLvoid SizeOpenGLScreen(GLsizei width, GLsizei height);

	/* Get Methods */
	const HDC GetHDC() const {return hDC;}
	const bool IsFullscreen() const {return fullscreen;}

private:
	/* Constructor */
	GLWindow(){};
	/* Instance of this class */
	static GLWindow* mInstance;

	// Is it fullscreen?
	bool fullscreen;

	RECT		globalRect;
	HDC			hDC;			// Private GDI Device Context
	HGLRC		hRC;			// Permanent Rendering Context
	HWND		hWnd;			// Holds Our Window Handle
	HINSTANCE	hinstance;		// Holds The Instance Of The Application
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
};

#endif