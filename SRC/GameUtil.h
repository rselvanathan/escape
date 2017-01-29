#ifndef __GAMEUTIL_H__
#define __GAMEUTIL_H__

#include <windows.h>									// Header File For The Windows Library
#include <stdio.h>										// Header File For The Standard Input/Output Functions
#include <stdlib.h>										// Header File For The Standard Library
#include <sstream>
#include <string> //Header class for a string
#include <list>
#include <vector>
#include <math.h>										// Header File For The Math header file
#include "gl.h"											// Header File For The OpenGL32 Library
#include "glu.h"									// Header File For The GLu32 Library
#include "glaux.h"									// Header File For The Glaux Library
#include "GLVector.h"
#include "Exception.h"
#include "SmartPtr.h"

using namespace std;
using namespace idllib;

#define SCREEN_WIDTH 800								// Define a screen width of 800 pixels
#define SCREEN_HEIGHT 600								// Define a screen height of 600 pixels
#define SCREEN_DEPTH 16									// Define 16 bit pixel depth

#define MAX_TEXTURES 1000		// The maximum amount of textures to load

typedef _LARGE_INTEGER largeInt; 

static const float Epsilon = 1e-6f;

static bool closeEnough(float f1, float f2)
 {
        // Determines whether the two floating-point values f1 and f2 are
        // close enough together that they can be considered equal.

       return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < Epsilon;
 }

// These are for our multitexture defines
#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1

#define GL_COMBINE_ARB						0x8570
#define GL_RGB_SCALE_ARB					0x8573

// Here are the multitexture function prototypes
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);

// Here we extern our function pointers for multitexturing capabilities
//extern PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
//extern PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;

#define MAX_TEXTURES 1000								// The maximum amount of textures to load

extern UINT g_Texture[MAX_TEXTURES];					// This stores the texture IDs

extern UINT h_Texture[MAX_TEXTURES];

#define GL_CLAMP_TO_EDGE	0x812F						// 

#define TERRAIN_ID 0

// A helper function to delete a pointer safely
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

// If M_PI has not been defined in math.h add it now
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define value to convert angles in degrees to radians and vice versa
#define DEG2RAD (M_PI/180)
#define RAD2DEG (180/M_PI)

// Two Helper macros that set Blending and Texture 2D on and off (Repeatedly used)
#define BLEND_TEX_ON	glEnable(GL_TEXTURE_2D);glEnable(GL_BLEND);glDisable(GL_DEPTH_TEST);glBlendFunc(GL_SRC_ALPHA, GL_ONE);  
#define BLEND_TEX_OFF   glBlendFunc(GL_ONE, GL_ONE);glEnable(GL_DEPTH_TEST);glDisable(GL_BLEND);glDisable(GL_TEXTURE_2D);

#endif