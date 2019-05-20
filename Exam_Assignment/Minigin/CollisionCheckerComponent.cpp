#include "MiniginPCH.h"
#include "CollisionCheckerComponent.h"
#include "Utils.h"
dae::CollisionCheckerComponent::CollisionCheckerComponent(GameObject * parent)
	:m_pParent(parent)
	,m_widthAndHeight({0,0})
	,m_offset({0,0})
{
}

void dae::CollisionCheckerComponent::Update(const float & deltaTime)
{
	bool hitSomething = false;

	// remake body
	m_collisionBody.x = m_pParent->GetTransform().GetPosition().x + m_offset.x;
	m_collisionBody.y = m_pParent->GetTransform().GetPosition().y + m_offset.y;
	m_collisionBody.w = m_widthAndHeight.x;
	m_collisionBody.h = m_widthAndHeight.y;

	// get objects from singleton
	std::vector<GameObject*> placeholder = CollisionManager::GetInstance().GetCollisionObjects();
	// check their bodies with your own
	for (int i{}; i < placeholder.size(); i++)
	{	
		if (IsRectOverlapping(m_collisionBody, placeholder[i]->GetComponent<CollisionComponent>()->getBody()))
		{
			// if they collide and the tag is "DestructableTerrain" destroy to collided, but only if the parent is a player
			if (placeholder[i]->GetComponent<CollisionComponent>()->GetTag() == collisionTag::Terrain)
				if (m_pParent->GetComponent<StateComponent>())
				{
					if (m_pParent->GetComponent<StateComponent>()->GetIsDigDug())
					{
						// clear its components so its empty
						placeholder[i]->ClearComponents();
						// remove it aswell from the collisionManagers vector, so it won't cause nlpters
						CollisionManager::GetInstance().RemoveCollisionObject(placeholder[i]);
					}
				}
			// else if they collide, check their tag and execute the command connected
			else
			{
				if (collisionEventMap[placeholder[i]->GetComponent<CollisionComponent>()->GetTag()])
				{
					collisionEventMap[placeholder[i]->GetComponent<CollisionComponent>()->GetTag()]->Execute(deltaTime, placeholder[i]);
					
				}
			}

			hitSomething = true;
		}

	}

	if (collisionEventMap[collisionTag::Nothing] && hitSomething == false)
	{
		collisionEventMap[collisionTag::Nothing]->Execute(deltaTime, nullptr);
	}
}

void dae::CollisionCheckerComponent::Render() const
{
}

void dae::CollisionCheckerComponent::SetWidthAndHeightBody(Point2f newWidthAndHeigh)
{
	m_widthAndHeight = newWidthAndHeigh;
}

void dae::CollisionCheckerComponent::SetOffset(Point2f newOffset)
{
	m_offset = newOffset;
}

void dae::CollisionCheckerComponent::addCollisionEvent(CollisionCommand *EventExecution, collisionTag tag)
{
	collisionEventMap[tag] = EventExecution;
}
