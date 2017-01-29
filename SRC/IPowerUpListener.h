#ifndef __IPOWERUPLISTENER_H__
#define __IPOWERUPLISTENER_H__

class IPowerUpListener
{
public:
	virtual void OnHealthPowerPicked() = 0;
	virtual void OnEnergyPowerPicked() = 0;
};

#endif
