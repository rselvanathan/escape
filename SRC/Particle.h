/* 
Reference : nehe.gamedev.net tutorial 19
			http://nehe.gamedev.net/tutorial/lessons_16__20/28002/
This class represent a Particle 

Author : Romesh Selvanthan
*/ 

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "GameUtil.h"

class Particle
{
public:
	Particle(){}
	~Particle(){}

	bool	active;							// Active (Yes/No)
	float	life;							// Particle Life (Alpha Value between 1 and 0
	float	fade;							// Fade Speed
	float	r;								// Red Value
	float	g;								// Green Value
	float	b;								// Blue Value
	CVector3 mPosition;					
	CVector3 mVelocity;
	CVector3 mAcceleration;
};

#endif