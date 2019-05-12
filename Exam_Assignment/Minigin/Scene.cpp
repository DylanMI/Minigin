#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

void dae::Scene::Add(SceneObject* object)
{
	mObjects.push_back(object);
}

void dae::Scene::Update(const float& deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

dae::Scene::~Scene()
{
	for (auto gameObject : mObjects)
	{
		delete gameObject;
	}
}

