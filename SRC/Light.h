#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "GameUtil.h"

class Light
{
public:
	Light(){}

	/*void PowerUpLight(){glEnable(GL_LIGHTING);glEnable(GL_COLOR_MATERIAL);glEnable(GL_NORMALIZE);}
	void SwitchOnLight(int light);
	void SwithOffLight(int light);
	void PowerOffLight(){glDisable(GL_LIGHTING);glDisable(GL_COLOR_MATERIAL);glDisable(GL_NORMALIZE);}
	void SetWorldAmbientLight(GLfloat ambient[]);
	void SetLight(GLfloat ambient[], GLfloat diffuse[] GLfloat specular[], GLfloat position[])
	{m_ambientColor = ambient; m_diffuseColor = diffuse; m_specularColor = specular; m_position = position;}
	void SetShininess(GLfloat shiny[]) {m_shiny = shiny;}

	void RenderShininess(){glMaterialfv(GL_FRONT,GL_SPECULAR,m_specularColor); glMaterialfv(GL_FRONT,GL_SHININESS,m_shiny);}
	void RenderLight();
	void RenderSpotLight(GLfloat cutoff, GLfloat direction[], GLfloat exponent); */ 

private:
	/*int m_light;

	GLfloat m_ambientColor[];
	GLfloat m_diffuseColor[];
	Glfloat m_specularColor[];
	GLfloat m_position[];
	GLfloat m_shiny[]; */ 
};

#endif