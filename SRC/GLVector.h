#ifndef __GLVECTOR_H__
#define __GLVECTOR_H__

#include <math.h>

struct CVector3
{
public:
	
	// A default constructor
	CVector3() {}

	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Return the Magnitude of the Vector
	float Length()
	{
		return (sqrt(x*x + y*y + z*z));
	}

	// Return a Normalized Vector
	CVector3 Normalize()
	{
		CVector3 out = CVector3(x,y,z);
		out = out / out.Length();
		return out;
	}

	// Return the Dot Product between this vector and another
	const float Dot(const CVector3& v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	// Get the cross product between this and another vector
	const CVector3 Cross(const CVector3& gv) const
	{
		return CVector3(y*gv.z-z*gv.y,z*gv.x-x*gv.z,x*gv.y-y*gv.x);
	}

	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector)
	{
		// Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector)
	{
		// Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}

	// Here overloading the / operator so we can divide vectors
	CVector3 operator/(CVector3 vVector)
	{
		// return the divided vector
		return CVector3(x/vVector.x, y/vVector.y, z/vVector.z); 
	}
	// Here we overloading the == operator so we can compare vectors
	bool operator==(CVector3 vVector)
	{
		// return compared value
		return (x == vVector.x, y == vVector.y, z==vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num)
	{
		// Return the scaled vector
		return CVector3(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float num)
	{
		// Return the scale vector
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;						
};

#endif 