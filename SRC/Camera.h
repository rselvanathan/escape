/*
This is the camera class that allows the world to be viewed. This current class works in a first person way.
This class also allows the fov value in gluperspective to be changed when sprinting. - (Very cool effect)

Author : Romesh Selvanathan

Reference : Graphics Template, Chris Child
*/

#ifndef _CAMERA_H
#define _CAMERA_H

#include "GameUtil.h"
#include "IEnemyListener.h"
#include "Entity.h"
#include "Matrix4.h"

class InputManager;

class CCamera
{

public:
	/* Constructor */
	CCamera();	
	
	/* Reset the Camera */
	void Reset();

	/* Get Methods */
	float GetSpeed() {return m_speed;}
	CVector3 Position() {return mPosition;}
	CVector3 View()		{	return m_vView;	}		 
	CVector3 UpVector() {	return m_vUpVector;	} 
	float GetPitch()	{return mPitch;}			  
	float GetYaw() {return mYaw;}					
	
	/* Set Methods */
	void SetViewVector(CVector3 v){m_vView = v;}	
	void SetUpVector(CVector3 v){m_vUpVector = v;}	  
	void SetRotations(float pitch, float yaw) {mPitch = pitch; mYaw = yaw;} 
	void SetIsSprinting(bool v){sprint = v;}
	void SetSpeed(float v) {m_speed = v;}
	void SetZPosition(float v) {mPosition.z = v;}
	void SetXPosition(float v) {mPosition.x = v;}
	
	/* 
	This changes the position, view, and up vector of the camera.
	 This is primarily used for initialization
	*/
	void PositionCamera(CVector3 position, CVector3 lookAt, CVector3 up);

	/*This rotates the camera's view around the position depending on the values passed in. */
	void RotateView(float angle, float X, float Y, float Z);

	/* This moves the camera's view by the mouse movements (First person view) */
	void SetViewByMouse(float mouseX, float mouseY); 

	/* This rotates the camera around a point (I.E. your character). */
	void RotateAroundPoint(CVector3 vCenter, float X, float Y, float Z);

	/* This strafes the camera left or right depending on the speed (+/-) */
	void StrafeCamera(float speed);

	/* This will move the camera forward or backward depending on the speed */
	void MoveCamera(float speed);

	/* This Will Update the camera values */ 
	void Update(float dt);

	// This uses gluLookAt() to tell OpenGL where to look
	void Look();

private:
	// Camera Position
	CVector3 mPosition;
	// The camera's view
	CVector3 m_vView;						
	// The camera's up vector
	CVector3 m_vUpVector;		
	// The camera's strafe vector
	CVector3 m_vStrafe;	

	// Rotations in X axis and Y Axis
	float mPitch, mYaw; 
	// the fov value for current perspective
	float fov;
	// Is camera sprinting
	bool sprint;
	// current speed of movement for camera
	float m_speed;
};

#endif