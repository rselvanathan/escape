#ifndef __ISWITCHLISTENER_H__
#define __ISWITCHLISTENER_H__

class ISwitchListener
{
public:
	virtual void OnSwitchTurned(bool _blue, bool _red) = 0;
	virtual void OnSwitchTurned2(bool _blue, bool _red, bool _yellow) = 0;
};

#endif 