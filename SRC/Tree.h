/*
This object just represents a tree in the world

Author : Romesh Selvanathan
*/ 

#ifndef __TREE_H__
#define __TREE_H__

#include "GameUtil.h"
#include "GameObject.h"

class Tree : public GameObject
{
public :
	/* Constructor */
	Tree();
	/* Destructor */ 
	virtual ~Tree();

	///////////////////////////////////////GameObject Inherited methods/////////////////////////////////
	/* NOTE: Has to be here due to it being a virtual = 0; method */ 
	virtual void OnCollision(Entity* o){}
	////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	SmartPtr<Model_3DS> treeModel;		// Model for the tree
};

#endif