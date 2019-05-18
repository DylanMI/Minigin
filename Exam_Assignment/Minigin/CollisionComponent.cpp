#include "MiniginPCH.h"
#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject * parent)
	:m_pParent(parent)
{
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(const float & )
{
}

void dae::CollisionComponent::Render() const
{
}

void dae::CollisionComponent::SetTag(collisionTag collTag)
{
	m_collTag = collTag;
}

dae::collisionTag dae::CollisionComponent::GetTag()
{
	return m_collTag;
}

void dae::CollisionComponent::SetBody(Rectf body)
{
	m_collisionBody = body;
}

dae::Rectf dae::CollisionComponent::getBody()
{
	return m_collisionBody;
}



