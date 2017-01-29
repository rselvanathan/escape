#include "TestCow.h"
#include "GameObject.h"
#include "GameUtil.h"
#include "PreLoader.h"


TestCow::TestCow() : GameObject("cow", PreLoader::GetInstance()->cowModel)//"Square")
{
}

TestCow::~TestCow()
{}

void TestCow::Update(int dt)
{
	GameObject::Update(dt);
}

void TestCow::PreRender()
{
}

void TestCow::Render()
{
	GameObject::Render();
}

void TestCow::PostRender()
{
}