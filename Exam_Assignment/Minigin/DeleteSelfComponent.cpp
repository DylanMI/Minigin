#include "MiniginPCH.h"
#include "DeleteSelfComponent.h"

dae::DeleteSelfComponent::DeleteSelfComponent(GameObject * parent, Scene & scene)
	: m_pParent(parent)
	, m_scene(scene)
	, m_isTicking(false)
{
}

void dae::DeleteSelfComponent::Update(const float & deltaTime)
{
	if (m_isTicking)
	{
		m_deleteTimer -= deltaTime;
	}

	if (m_deleteTimer <= 0.0f)
	{
		m_pParent->ClearComponents();
		// delete yourself
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
