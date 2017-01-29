#ifndef __TESTCOW_H__
#define __TESTCOW_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "CollisionManager.h"

class TestCow : public GameObject
{
public :
	TestCow();
	~TestCow();

	virtual void Update(int dt);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual bool CollisionTest(Entity* o) { return false; }
	virtual void OnCollision(Entity* o){}

	void SetCollisionListener(CollisionManager& mCollisionManager)
	{mCollisionManager.AddCollisionListener(this);}

private:
};

#endif