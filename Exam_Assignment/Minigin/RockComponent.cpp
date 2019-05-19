#include "MiniginPCH.h"
#include "RockComponent.h"

dae::RockComponent::RockComponent(GameObject * parent)
	: m_pParent(parent)
	, m_isBreaking(false)
	, m_isFalling(false)
	, m_fallSpeed(1.0f)
	, m_breakTimer(1.0f)
{
}

void dae::RockComponent::Update(const float & deltaTime)
{
	// if it is falling, then fall
	if (m_isFalling)
	{
		Point2f currPos = { m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y };
		Point2f newPos = { currPos.x, currPos.y - (deltaTime * m_fallSpeed) };
		m_pParent->SetPosition(newPos);

	}

	// if it is breaking, stop falling and break
	if (m_isBreaking)
	{
		m_isFalling = false;

		// further the state timer
		m_breakTimer -= deltaTime;
		// and change the state of the parent accordingly
		if (m_breakTimer < 0.6f)
		{

		}
		else if (m_breakTimer < 0.3f)
		{

		}
		else if (m_breakTimer < 0.1f)
		{

		}
		else if (m_breakTimer <= 0.0f)
		{

		}


	}

}

void dae::RockComponent::Render() const
{
}

void dae::RockComponent::SetFallSpeed(float newSpeed)
{
	m_fallSpeed = newSpeed;
}

void dae::RockComponent::SetIsFalling(bool isFalling)
{
	m_isFalling = isFalling;
}

void dae::RockComponent::SetIsBreaking(bool isBreaking)
{
	m_isBreaking = isBreaking;
}

bool dae::RockComponent::GetIsFalling()
{
	return m_isFalling;
}

bool dae::RockComponent::GetIsBreaking()
{
	return m_isBreaking;
}

