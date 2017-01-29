// References http://www.dhpoware.com/demos/index.html
#ifndef __MATRIX4_H__
#define __MATRIX4_H__

class CVector3;

class Matrix4
{
public:
	Matrix4() {}
	Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
	~Matrix4() {}

	static const Matrix4 IDENTITY;

	void Identity();
	// create a rotation matrix with angle (rad) around axis of rotation vector
	void SetRotation(const CVector3 &axis, float degrees);
	// get euler values of rotation order head(y), pitch(x), roll(z) of matrix (Nasa standard)
	void GetEularAngles(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
	// set euler values of rotation order head(y), pitch(x), roll(z) of matrix (Nasa standard)
	void SetEularAngles(float headDegrees, float pitchDegrees, float rollDegrees);

	/////////////////////////////Operators/////////////////////////

	float *operator[](int row);
    const float *operator[](int row) const;

    bool operator==(const Matrix4 &rhs) const;
    bool operator!=(const Matrix4 &rhs) const;

    Matrix4 &operator+=(const Matrix4 &rhs);
    Matrix4 &operator-=(const Matrix4 &rhs);
    Matrix4 &operator*=(const Matrix4 &rhs);
    Matrix4 &operator*=(float scalar);
    Matrix4 &operator/=(float scalar);

    Matrix4 operator+(const Matrix4 &rhs) const;
    Matrix4 operator-(const Matrix4 &rhs) const;
    Matrix4 operator*(const Matrix4 &rhs) const;
    Matrix4 operator*(float scalar) const;
    Matrix4 operator/(float scalar) const;

	/////////////////////////////////////////////////////////////////

private:
	float mtx[4][4];
};

#endif 