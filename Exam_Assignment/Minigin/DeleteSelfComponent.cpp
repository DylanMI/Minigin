#include "MiniginPCH.h"
#include "DeleteSelfComponent.h"

dae::DeleteSelfComponent::DeleteSelfComponent(GameObject * parent, Scene & scene)
	: BaseComponent(parent)
	, m_scene(scene)
	, m_isTicking(false)
{
}

void dae::DeleteSelfComponent::Update(const float & deltaTime)
{
	if (m_isTicking)
	{
		m_deleteTimer -= deltaTime;
		if (m_deleteTimer <= 0.0f)
		{
			if (m_pParent->GetComponent<CollisionComponent>() != nullptr)
			{
				// de register yourself
				CollisionManager::GetInstance().RemoveCollisionObject(m_pParent);
			}
			
			// delete yourself
			m_scene.Remove(m_pParent);
		}
	}

}

void dae::DeleteSelfComponent::Render() const
{
}

void dae::DeleteSelfComponent::StartSelfDestruct(float time)
{
	m_deleteTimer = time;
	m_isTicking = true;
}

void dae::DeleteSelfComponent::KillNow()
{
	if (m_pParent->GetComponent<CollisionComponent>() != nullptr)
	{
		// de register yourself
		CollisionManager::GetInstance().RemoveCollisionObject(m_pParent);

	}

	m_pParent->ClearComponents();
}

