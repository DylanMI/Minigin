#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "BaseCharacter.h"
#include <algorithm>
unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

void dae::Scene::Add(SceneObject* object)
{
	mObjects.push_back(object);
}

void dae::Scene::Remove(SceneObject * object)
{
	if (dynamic_cast<GameObject*>(object))
	{
		dynamic_cast<GameObject*>(object)->ClearComponents();
	}
	delete object;
	mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), object), mObjects.end());
}

void dae::Scene::Update(const float& deltaTime)
{
	for (int i{}; i < mObjects.size(); i++)
	{
		mObjects[i]->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (int i{}; i < mObjects.size(); i++)
	{
		mObjects[i]->Render();
	}
}

dae::Scene::~Scene()
{
	for (auto gameObject : mObjects)
	{
		delete gameObject;
	}
}

