/* Reference : Asteroids (Chris Child) */ 

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "GameUtil.h"

typedef list< SmartPtr <CVector3> > Vec3List;

class Shape
{
public :
	Shape();
	~Shape();

	void Render(GLenum mType);
	void LoadShape(const string& shape_filename);
	
private:
	//bool mLoop;
	GLenum mType;
	//Vec3 mRGB;
	Vec3List mPoints;
};

#endif