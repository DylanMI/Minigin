#include "MiniginPCH.h"
#include "CollisionCheckerComponent.h"
#include "Utils.h"
dae::CollisionCheckerComponent::CollisionCheckerComponent(GameObject * parent)
	:m_pParent(parent)
{
}

void dae::CollisionCheckerComponent::Update(const float & deltaTime)
{
	// remake body
	m_collisionBody.x = m_pParent->GetTransform().GetPosition().x;
	m_collisionBody.y = m_pParent->GetTransform().GetPosition().y;
	m_collisionBody.w = m_widthAndHeight.x;
	m_collisionBody.h = m_widthAndHeight.y;

	// get objects from singleton
	std::vector<GameObject*> placeholder = CollisionManager::GetInstance().GetCollisionObjects();
	// check their bodies with your own
	for (int i{}; i < placeholder.size(); i++)
	{
		
		if (IsRectOverlapping(m_collisionBody, placeholder[i]->GetComponent<CollisionComponent>()->getBody()))
		{
			// if they collide and the tag is "DestructableTerrain" destroy to collided
			if (placeholder[i]->GetComponent<CollisionComponent>()->GetTag() == collisionTag::Destructable)
			{
				placeholder[i]->ClearComponents();
			}
			// else if they collide, check their tag and execute the command connected
			else
			{
				collisionEventMap[placeholder[i]->GetComponent<CollisionComponent>()->GetTag()]->Execute(deltaTime);
			}
		}

		
	}

	
}

void dae::CollisionCheckerComponent::Render() const
{
}

void dae::CollisionCheckerComponent::SetWidthAndHeightBody(Point2f newWidthAndHeigh)
{
	m_widthAndHeight = newWidthAndHeigh;
}

void dae::CollisionCheckerComponent::addCollisionEvent(Command * , collisionTag )
{
}
