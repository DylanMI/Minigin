#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		delete m_pComponents[i];
	}
}

void dae::GameObject::Update(const float& deltaTime)
{
	// update all the components
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		m_pComponents[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	// legacy
	const auto pos = mTransform.GetPosition();
	// ~legacy

	// render all the components
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		m_pComponents[i]->Render();
	}
}

void dae::GameObject::Move(Point2f direction, float deltaTime)
{

	// right
	if (direction.x == 1)
	{
		if(GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::RIGHT);
	}
	// left
	if (direction.x == -1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::LEFT);
	}
	// up
	if (direction.y == 1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::UP);
	}
	//down
	if (direction.y == -1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::DOWN);
	}
	Point2f newpos;
	// the moving
	newpos = { mTransform.GetPosition().x , mTransform.GetPosition().y };
	newpos.x += (direction.x * m_speed) * deltaTime;
	newpos.y += (-direction.y * m_speed) * deltaTime;


}

void dae::GameObject::SetPosition(Point2f pos)
{
	mTransform.SetPosition(pos.x, pos.y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform()
{
	return mTransform;
}

float dae::GameObject::GetSpeed()
{
	return m_speed;
}

void dae::GameObject::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}



void dae::GameObject::AddComponent(BaseComponent * component)
{
	m_pComponents.push_back(component);
}

void dae::GameObject::ClearComponents()
{
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		delete m_pComponents[i];
	}
	m_pComponents.resize(0);
}
