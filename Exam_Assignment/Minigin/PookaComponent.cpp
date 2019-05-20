#include "MiniginPCH.h"
#include "PookaComponent.h"

dae::PookaComponent::PookaComponent(GameObject * parent)
	:m_pParent(parent)
	,m_currentState(State::WANDERING)
	,m_direction({1,0})
	,m_previousLocation({0,0})
	,m_GhostTimer(m_GhostTime)
{
}

void dae::PookaComponent::Update(const float & deltaTime)
{
	switch (m_currentState)
	{
	case State::WANDERING:
		// further ghost timer
		m_GhostTimer -= deltaTime;
		// hold previous location, for if you wander into a wall
		m_previousLocation = { m_pParent->GetTransform().GetPosition().x , m_pParent->GetTransform().GetPosition().y };
		// move 
		m_pParent->Move(m_direction,deltaTime);
		break;

	}

}

void dae::PookaComponent::Render() const
{
}

void dae::PookaComponent::RandomizeDirection()
{
}

void dae::PookaComponent::PutBackAFrame()
{
}
