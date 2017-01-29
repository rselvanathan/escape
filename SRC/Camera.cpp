/*
This is the camera class that allows the world to be viewed. This current class works in a first person way.
This class also allows the fov value in gluperspective to be changed when sprinting. - (Very cool effect)

Author : Romesh Selvanathan

Reference : Graphics Template, Chris Child
*/

#include "GameUtil.h"
#include "Camera.h"
#include "Entity.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "Shoot.h"
#include "GameWorld.h"

/* Constructor */
CCamera::CCamera() 
{
	m_vView = CVector3(0.0, 1.0, 0.5);				// Init a starting view vector (looking up and out the screen) 
	m_vUpVector	= CVector3(0.0, 0.0, 1.0);			// Init a standard up vector (Rarely ever changes)
	mYaw = mPitch = 0.0f;							// Set Yaw And Pitch

	fov = 45.0f; sprint = false;
}

/* Reset the Camera */
void CCamera::Reset()
{
	m_vView = CVector3(0.0, 1.0, 0.5);				// Init a starting view vector (looking up and out the screen) 
	m_vUpVector	= CVector3(0.0, 0.0, 1.0);			// Init a standard up vector (Rarely ever changes)
	mYaw = mPitch = 0.0f;							// Set Yaw And Pitch

	fov = 45.0f; sprint = false;
}

/* 
	This changes the position, view, and up vector of the camera.
	 This is primarily used for initialization
*/
void CCamera::PositionCamera(CVector3 position, CVector3 lookAt, CVector3 up)
{
	mPosition = position;			    // Assign the position
	m_vView     = lookAt;				// Assign the view
	m_vUpVector = up;					// Assign the up vector	
}

/* This moves the camera's view by the mouse movements (First person view) */
void CCamera::SetViewByMouse(float mouseX, float mouseY)
{
	static float currentRotX = 0.0f;	

	// Bring the number down to a reasonable amount
	mYaw = mouseX / 500.0f;		
	mPitch = mouseY / 500.0f;		

	// Here we keep track of the current rotation (for up and down) so that
	// we can restrict the camera from doing a full 360 loop.
	currentRotX -= mPitch;  

	// If the current rotation (in radians) is greater than 1.0, we want to cap it.
	if(currentRotX > 1.0f)
		currentRotX = 1.0f;
	// Check if the rotation is below -1.0, if so we want to make sure it doesn't continue
	else if(currentRotX < -1.0f)
		currentRotX = -1.0f;
	// Otherwise, we can rotate the view around our position
	else
	{
		// To find the axis we need to rotate around for up and down
		// movements, we need to get a perpendicular vector from the
		// camera's view vector and up vector.  This will be the axis.
		CVector3 vAxis = (m_vView-mPosition).Cross(m_vUpVector);
		vAxis = vAxis.Normalize();

		// Rotate around our perpendicular axis and along the y-axis
		RotateView(mPitch, vAxis.x, vAxis.y, vAxis.z);
	} 

	// Rotate around the y axis no matter what the currentRotX is
	RotateView(mYaw, 0, 1, 0);
}

/* This rotates the camera around a point (I.E. your character). */
void CCamera::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;

	// Get the view vector (The direction we are facing)
	CVector3 vView = m_vView - mPosition;		

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	// Find the new y position for the new rotated point
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = mPosition + vNewView;
}

/* This strafes the camera left or right depending on the speed (+/-) */
void CCamera::StrafeCamera(float speed)
{	
	m_speed = speed;

	// Add the strafe vector to our position
	mPosition.x += m_vStrafe.x * m_speed;
	mPosition.z += m_vStrafe.z * m_speed;

	// Add the strafe vector to our view
	m_vView.x += m_vStrafe.x * m_speed;
	m_vView.z += m_vStrafe.z * m_speed;  

}

/* This will move the camera forward or backward depending on the speed */
void CCamera::MoveCamera(float speed)
{
	m_speed = speed;

	//if(!move){
	// Get the current view vector (the direction we are looking)
	CVector3 vVector = m_vView - mPosition;
	vVector = vVector.Normalize();

	mPosition.x += vVector.x * m_speed;		// Add our acceleration to our position's X
	//m_vPosition.y += vVector.y * speed;		// Add our acceleration to our position's Y
	mPosition.z += vVector.z * m_speed;		// Add our acceleration to our position's Z
	m_vView.x += vVector.x * m_speed;			// Add our acceleration to our view's X
	//m_vView.y += vVector.y * speed;			// Add our acceleration to our view's Y
	m_vView.z += vVector.z * m_speed;			// Add our acceleration to our view's Z
	//}
	//else
	//	move = false; 
}

/* This Will Update the camera values */ 
void CCamera::Update(float dt) 
{
	// These two if statments create the special effect where the camera view will zoom out
	// when sprinting giving a very cool effect. It gives that effect of going in high speed.
	// Its very simple effect where I just add and subtract the "fov" value to make sure a smooth
	// increase and decrease occurs 
	// if sprinting
	if(sprint){
		// add a certain amount to current fov
		fov += 50 *dt;
		// stop if you go beyond a certian value
		if(fov > 65)
			fov = 65;
	}
	// if not sprinting
	else{
		// and if the value is greater than normal fov
		if(fov > 45.0f){
			// decrease the value
			fov -= 90 *dt;
			// till you go below the normal fov
			if(fov < 45.0f)
				fov = 45.0f;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
														// The parameters are:
														// (view angle, aspect ration of the width to the height, 
														//  The closest distance to the camera before it clips, 
				  // FOV		// Ratio				//  The farthest distance before it stops drawing)
	gluPerspective(fov,(GLfloat)800/(GLfloat)600, .5f, 7000.f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialize a variable for the cross product result
	CVector3 vCross = (m_vView-mPosition).Cross(m_vUpVector);

	// Normalize the strafe vector
	m_vStrafe = vCross.Normalize();
}

// This uses gluLookAt() to tell OpenGL where to look
void CCamera::Look()
{
	// Give openGL our camera position, then camera view, then camera up vector
	gluLookAt(mPosition.x, mPosition.y, mPosition.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z); 
}
