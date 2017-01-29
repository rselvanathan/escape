#ifndef __IMOUSELISTENER_H__
#define __IMOUSELISTENER_H__

class IMouseListener
{
public:
	virtual void OnMouseMove(float x, float y)  = 0;
};

#endif