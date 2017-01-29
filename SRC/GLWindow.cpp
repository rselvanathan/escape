/* 
This class creates OpenGL Window. This class is a singleton to make sure only one window is created
at any time.

Author : Romesh Selvanathan
*/

#include "GLWindow.h"
#include "GameUtil.h"

/* Obtain a Single Instance of this Window */ 
GLWindow* GLWindow::mInstance;

/* Destructor */
GLWindow::~GLWindow()
{
}

/* Initialise the Window */
bool GLWindow::Init(HINSTANCE hInstance, bool fullscreenFlag)
{
	fullscreen = fullscreenFlag;
	hinstance = hInstance;

	// Try to create a Window
	try	{
		// If fullscreen then create the fullscreen window
		if(fullscreen){
			hWnd = CreateWindowGL("Escape",SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_DEPTH,fullscreen,hinstance);
		}
		// otherwise create a normal window
		else {
			hWnd = CreateWindowGL("Escape",SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_DEPTH,fullscreen,hinstance);
		}
		// Obtain the client rectangle
		GetClientRect(hWnd, &globalRect);
		// Initialise the OpenGL Window
		InitOpenGL(globalRect.right, globalRect.bottom);
	} catch (Exception &e) {
		// if error show a messagebox with the error then kill an close the program
		MessageBox(NULL,e.GetReason(),"ERROR",MB_OK|MB_ICONEXCLAMATION);
		KillGLWindow();								// Reset The Display
		PostQuitMessage(0);
	}


	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glEnable(GL_TEXTURE_2D);							// Enable texture mapping
	glEnable(GL_CULL_FACE);								// Turn on back face culling
	glEnable(GL_SMOOTH);								// Makes Everythign SMooth
	glEnable(GL_LEQUAL);								// Type of Depth Testing

	// Everything went ok
	return true;

}

/* Initialise OpenglWindow */
void GLWindow::InitOpenGL(int width, int height)
{
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
		throw Exception("Can't Create A GL Device Context.");
	if(!bSetupPixelFormat())						// Can we set up a Pixel Format?
		PostQuitMessage(0);
	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
		throw Exception("Can't Create A GL Rendering Context.");
	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
		throw Exception("Can't Activate The GL Rendering Context.");

	SizeOpenGLScreen(width, height);
}


void GLWindow::SizeOpenGLScreen(int width, int height)			// Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero error
	{
		height=1;										// Make the Height Equal One
	}

	glViewport(0,0,width,height);						// Make our viewport the whole window
														// We could make the view smaller inside
														// Our window if we wanted too.
														// The glViewport takes (x, y, width, height)
														// This basically means, what our our drawing boundries

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
														// The parameters are:
														// (view angle, aspect ration of the width to the height, 
														//  The closest distance to the camera before it clips, 
				  // FOV		// Ratio				//  The farthest distance before it stops drawing)
	gluPerspective(45,(GLfloat)width/(GLfloat)height, .5f, 7000.f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
/* Setup the Pixel Format for the Window */
bool GLWindow::bSetupPixelFormat()
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	PIXELFORMATDESCRIPTOR pfd;			// pfd Tells Windows How We Want Things To Be

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);			// Set the size of the structure
    pfd.nVersion = 1;									// Always set this to 1
														// Pass in the appropriate OpenGL flags
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;					// We want the standard mask (this is ignored anyway)
    pfd.iPixelType = PFD_TYPE_RGBA;						// We want RGB and Alpha pixel type
    pfd.cColorBits = 32;						// Here we use our #define for the color bits
    pfd.cDepthBits = 32;						// Depthbits is ignored for RGBA, but we do it anyway
    pfd.cAccumBits = 0;									// No special bitplanes needed
    pfd.cStencilBits = 0;								// We desire no stencil bits

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
		throw Exception("Can't Find A Suitable PixelFormat.");
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
		throw Exception("Can't Set The PixelFormat.");

	return true;	
}

/* Change the window to fullscreen */
void GLWindow::ChangeToFullscreen(int width, int height, int pixels)
{
	DEVMODE dmSettings;									// Device Mode variable

	memset(&dmSettings,0,sizeof(dmSettings));			// Makes Sure Memory's Cleared
	dmSettings.dmSize=sizeof(dmSettings);				// Size Of The Devmode Structure
	dmSettings.dmPelsWidth	= width;					// Selected Screen Width
	dmSettings.dmPelsHeight	= height;					// Selected Screen Height
	dmSettings.dmBitsPerPel = pixels;					// Selected Screen Pixels
	dmSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	// Try To Set Selected Mode.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
	if (ChangeDisplaySettings(&dmSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		throw Exception("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card.");
}

/* Kill the Window */
void GLWindow::KillGLWindow()
{
	if(fullscreen)	{									// Are We In Fullscreen Mode?
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	} 
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);

		hRC=NULL;										// Set RC To NULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("Graphics Template",hinstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hinstance=NULL;									// Set hInstance To NULL
	}
}

/* Create a Window */
HWND GLWindow::CreateWindowGL(const char* title, int width, int height, int bits, bool fullscreenflag, HINSTANCE hInstance)
{
	HWND		hwnd;
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hinstance			= hInstance;				// Grab An Instance For Our Window
	memset(&wc, 0, sizeof(WNDCLASS));							// Init the size of the class(so that the other variables of wc are set to 0/NULL)
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.hInstance		= hinstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.lpszClassName	= "Graphics Template";								// Set The Class Name
	ShowCursor(FALSE);
	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
		throw Exception("Failed To Register The Window Class.");

	if (fullscreenflag)												// Attempt Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ChangeToFullscreen(width, height, bits);
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hwnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"Graphics Template",								// Class Name
								title,								// Window Title
								dwStyle, 							// Defined Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hinstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{	throw Exception("Window Creation Error."); }

	ShowWindow(hwnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hwnd);						// Slightly Higher Priority
	SetFocus(hwnd);									// Sets Keyboard Focus To The Window

	return hwnd;									// Success
}

// Declaration For WndProc
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LONG    lRet = 0; 
    PAINTSTRUCT    ps;

    switch (uMsg)
	{ 
    case WM_SIZE:										// If the window is resized
		if(!GLWindow::GetInstance()->IsFullscreen())	// Do this only if we are NOT in full screen
		{
			GLWindow::GetInstance()->SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));// LoWord=Width, HiWord=Height
			//GetClientRect(hWnd, &g_rRect);					// Get the window rectangle
		}
        break; 
 
	case WM_PAINT:										// If we need to repaint the scene
		BeginPaint(hWnd, &ps);							// Init the paint struct		
		EndPaint(hWnd, &ps);							// EndPaint, Clean up
		break;

	case WM_KEYDOWN:
		switch(wParam) {								// Check if we hit a key
			case VK_ESCAPE:								// If we hit the escape key
				PostQuitMessage(0);						// Send a QUIT message to the window
				break;
			case VK_SPACE:								//If spacebar is pressed
			
				{
				}
				break;
			case VK_RETURN:
				break;
		}
		break;
 
    case WM_DESTROY:									// If the window is destroyed
        PostQuitMessage(0);								// Send a QUIT Message to the window
        break; 
     
	case WM_TIMER: //Check if a timer is triggered
		switch (wParam) 
		{ 
		} 

    default:											// Return by default
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
        break; 
    } 
 
    return lRet;										// Return by default
}