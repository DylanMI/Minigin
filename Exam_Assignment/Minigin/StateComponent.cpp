#include "MiniginPCH.h"
#include "StateComponent.h"

dae::StateComponent::StateComponent(GameObject * parent)
	: m_pParent(parent)
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
