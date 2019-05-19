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
	// make it 4 axis instead of ... ehm, more? (preventing diagonal)
	Point2f correctedDirection{};
	if (direction.x == 1)
	{
		correctedDirection.x = 1;
		correctedDirection.y = 0;
	}
	else if (direction.x == -1)
	{
		correctedDirection.x = -1;
		correctedDirection.y = 0;
	}
	else if (direction.y == 1)
	{
		correctedDirection.x = 0;
		correctedDirection.y = 1;
	}
	else if (direction.y == -1)
	{
		correctedDirection.x = 0;
		correctedDirection.y = -1;
	}

	// right
	if (correctedDirection.x == 1)
	{
		if(GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::RIGHT);
	}
	// left
	if (correctedDirection.x == -1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::LEFT);
	}
	// up
	if (correctedDirection.y == 1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::UP);
	}
	//down
	if (correctedDirection.y == -1)
	{
		if (GetComponent<StateComponent>() != nullptr)GetComponent<StateComponent>()->SetState(State::DOWN);
	}
	Point2f newpos;
	// the moving
	newpos = { mTransform.GetPosition().x , mTransform.GetPosition().y };
	newpos.x += (correctedDirection.x * m_speed) * deltaTime;
	newpos.y += (-correctedDirection.y * m_speed) * deltaTime;
	SDL_log(correctedDirection.x);
	SDL_log(correctedDirection.y);
	// the collision checking


	// pushing the change
	SetPosition(newpos);
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
