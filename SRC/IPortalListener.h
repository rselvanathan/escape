#ifndef __IPORTALISTENER_H__
#define __IPORTALISTENER_H__

class IPortalListener
{
public:
	virtual void OnPortalEnter(int portal) = 0;
};

#endif