/* Reference : Asteroids (Chris Child) */ 

#include "Shape.h"
#include "GameUtil.h"
#include <fstream>

Shape::Shape()
{}

Shape::~Shape()
{}

void Shape::LoadShape(const string& shape_filename)
{
	string filename;
	filename = "..//..//ASSETS//SHAPES//";
	filename += shape_filename;

	ifstream shape_file(filename.c_str(), ios::in | ios::binary);

	//if(!shape_file)
		//cerr << "Error Opening " << shape_filename; exit(1);

	if(shape_file){
		//shape_file >> mType;
		//shape_file >> mRGB;
		while(!shape_file.eof()){
			float x, y, z;
			shape_file >> x >> y >> z;
			SmartPtr<CVector3> vec = new CVector3(x, y, z);
			mPoints.push_back(vec);
		}
	}
}

void Shape::Render(GLenum mType)
{
	//glDisable(GL_LIGHTING);

	glBegin(mType);
		//glColor3f(mRGB[0], mRGB[1], mRGB[2]);
		for(Vec3List::iterator it = mPoints.begin(); it != mPoints.end(); ++it){
			SmartPtr<CVector3> vec = (*it);
			glVertex3f(vec->x, vec->y, vec->z);
		}
	glEnd();

	//glEnable(GL_LIGHTING);
}