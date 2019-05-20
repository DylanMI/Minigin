#include "MiniginPCH.h"
#include "PookaComponent.h"

dae::PookaComponent::PookaComponent(GameObject * parent)
	:m_pParent(parent)
	,m_currentState(State::WANDERING)
	,m_direction({1,0})
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
		// move 
		m_pParent->Move(m_direction,deltaTime);
		break;

	}

}

void dae::PookaComponent::Render() const
{
}

void dae::PookaComponent::ShiftDirection()
{
	Point2f prevDirection = m_direction;

	
	do
	{
		int randomizer = rand() % 4;
		switch (randomizer)
		{
		case 0:
			m_direction = { 1,0 };
			break;
		case 1:
			m_direction = { -1,0 };
			break;
		case 2:
			m_direction = { 0,1 };
			break;
		case 3:
			m_direction = { 0,-1 };
			break;
		default:
			break;
		}
	} while (prevDirection.x == m_direction.x && prevDirection.y == m_direction.y);
	

}

void dae::PookaComponent::PutBackAFrame(float deltatime)
{
	m_pParent->Move(Point2f{ -m_direction.x, -m_direction.y }, deltatime);
}
