/*
This object just represents a tree in the world

Author : Romesh Selvanathan
*/ 

#include "Tree.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "PreLoader.h"

Tree::Tree() : GameObject("tree", NULL)
{
	treeModel = new Model_3DS();
	treeModel->Load("elm.3ds");
	SetModel(treeModel);
}

Tree::~Tree()
{GameObject::~GameObject();}
