#include "Light.h"
#include "GameUtil.h"

/*
Light::Light() 
{
	//SwitchOnLight(light); 
}

void Light::SwitchOnLight(int light)
{
	switch (light)
	{
	case 0 : glEnable(GL_LIGHT0); break;
	case 1 : glEnable(GL_LIGHT1); break;
	case 2 : glEnable(GL_LIGHT2); break;
	case 3 : glEnable(GL_LIGHT3); break;
	case 4 : glEnable(GL_LIGHT4); break;
	case 5 : glEnable(GL_LIGHT5); break;
	case 6 : glEnable(GL_LIGHT6); break;
	case 7 : glEnable(GL_LIGHT7); break;
	}

	m_light = light;
}

void Light::SwithOffLight(int light)
{
	switch (light)
	{
	case 0 : glDisable(GL_LIGHT0); break;
	case 1 : glDisable(GL_LIGHT1); break;
	case 2 : glDisable(GL_LIGHT2); break;
	case 3 : glDisable(GL_LIGHT3); break;
	case 4 : glDisable(GL_LIGHT4); break;
	case 5 : glDisable(GL_LIGHT5); break;
	case 6 : glDisable(GL_LIGHT6); break;
	case 7 : glDisable(GL_LIGHT7); break;
	}

	m_light = NULL;
}

void Light::SetWorldAmbientLight(GLfloat ambient[])
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void Light::RenderLight()
{
	glLightfv(m_light, GL_AMBIENT, m_ambientColor);
	glLightfv(m_light, GL_DIFFUSE, m_diffuseColor);
	glLightfv(m_light, GL_SPECULAR, m_specularColor);
    glLightfv(m_light, GL_POSITION, m_position);
}

void Light::RenderSpotLight(GLfloat cutoff, GLfloat direction[], GLfloat exponent)
{
	glLightf(m_light, GL_SPOT_CUTOFF, cutoff);
	//glLightfv(m_light, GL_SPOT_DIRECTION, direction);
	glLightf(m_light,  GL_SPOT_EXPONENT, exponent);
}*/ 