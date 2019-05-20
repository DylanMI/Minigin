#include "MiniginPCH.h"
#include "StateComponent.h"

dae::StateComponent::StateComponent(GameObject * parent, bool isDigDug)
	: m_pParent(parent)
	, m_isDigDug(isDigDug)
{
}

void dae::StateComponent::Update(const float &)
{
}

void dae::StateComponent::Render() const
{
}

dae::State dae::StateComponent::GetState()
{
	return m_CurrentState;
}

void dae::StateComponent::SetState(State newState)
{
	m_CurrentState = newState;
}

bool dae::StateComponent::GetIsDigDug()
{
	return m_isDigDug;
}
