#include "MiniginPCH.h"
#include "CollisionComponent.h"

dae::CollisionComponent::CollisionComponent(GameObject * parent)
	: BaseComponent(parent)
{
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(const float & )
{
	// update the collisionBody
	m_collisionBody = Rectf{ m_pParent->GetTransform().GetPosition().x,m_pParent->GetTransform().GetPosition().y ,m_WidthAndHeight.x,m_WidthAndHeight.y };

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

void dae::CollisionComponent::SetWidthAndHeight(Point2f WidthAndHeight)
{
	m_WidthAndHeight = WidthAndHeight;
}

dae::Rectf dae::CollisionComponent::getBody()
{
	return m_collisionBody;
}



