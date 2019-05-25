#include "MiniginPCH.h"
#include "RockComponent.h"

dae::RockComponent::RockComponent(GameObject * parent)
	: m_pParent(parent)
	, m_isBreaking(false)
	, m_isActuallyFalling(false)
	, m_isFalling(false)
	, m_fallSpeed(1.0f)
	, m_breakTimer(1.0f)
	, m_fallTimer(m_fallTime)
{
}

void dae::RockComponent::Update(const float & deltaTime)
{
	// if it is falling, then fall
	if (m_isFalling)
	{
		// after a specific time ofcourse
		m_fallTimer -= deltaTime;
		if (m_fallTimer < 0)
		{
			m_isActuallyFalling = true;
			Point2f currPos = { m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y };
			Point2f newPos = { currPos.x, currPos.y - (deltaTime * m_fallSpeed) };
			m_pParent->SetPosition(newPos);
		}
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
			m_pParent->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_Two.png"));
		}
		if (m_breakTimer < 0.3f)
		{
			m_pParent->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_Three.png"));

		}
		if (m_breakTimer < 0.1f)
		{
			m_pParent->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_Four.png"));

		}
		if (m_breakTimer <= 0.0f)
		{
			// kill all the victims
			for (size_t i{}; i < m_victims.size(); i++)
			{
				m_victims[i]->GetComponent<DeleteSelfComponent>()->KillNow();

			}
			CollisionManager::GetInstance().RemoveCollisionObject(m_pParent);
			m_pParent->ClearComponents();
		}


	}

	// take the victims with you
	if (!m_victims.empty())
	{
		for (size_t i{}; i < m_victims.size(); i++)
		{
			m_victims[i]->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x,m_pParent->GetTransform().GetPosition().y });
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

void dae::RockComponent::AddVictim(GameObject * newVictim)
{
	m_victims.push_back(newVictim);
}

bool dae::RockComponent::IsVictimAlreadyRegistered(GameObject * Victim)
{
	if (std::find(m_victims.begin(), m_victims.end(), Victim) != m_victims.end()) 
	{
		return true;
	}
	else return false;
}

bool dae::RockComponent::GetIsFalling()
{
	return m_isActuallyFalling;
}

bool dae::RockComponent::GetIsBreaking()
{
	return m_isBreaking;
}

