#include "MiniginPCH.h"
#include "RockComponent.h"

dae::RockComponent::RockComponent(GameObject * parent)
	: m_pParent(parent)
	, m_isBreaking(false)
	, m_isFalling(false)
	, m_fallSpeed(1.0f)
{
}

void dae::RockComponent::Update(const float & deltaTime)
{
	// if it is falling, then fall
	if (m_isFalling)
	{
		Point2f currPos = { m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y };

	}

	// if it is breaking, stop falling and break
	if (m_isBreaking)
	{
		m_isFalling = false;

	}

}

void dae::RockComponent::Render() const
{
}

void dae::RockComponent::SetFallSpeed(float newSpeed)
{
}

void dae::RockComponent::SetIsFalling()
{
}

void dae::RockComponent::Break()
{
}
