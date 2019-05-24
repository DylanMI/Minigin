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
		if (m_deleteTimer <= 0.0f)
		{
			if (m_pParent->GetComponent<CollisionComponent>() != nullptr)
			{
				// de register yourself
				CollisionManager::GetInstance().RemoveCollisionObject(m_pParent);
			}
			
			
			HandleEvent();
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
	HandleEvent();

	m_scene.Remove(m_pParent);
}

void dae::DeleteSelfComponent::HandleEvent()
{
	const int height = 480;
	
	// check if pooka
	if (m_pParent->GetComponent<PookaComponent>() != nullptr)
	{
		// call event accordingly
						// set it to the right texture
		if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 1)
		{
			// Yellow
			Messenger::instance().Notify(Event::EVENT_DIEDONFIRSTLAYER_POOKA);

		}
		else if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 2)
		{
			// Orange 
			Messenger::instance().Notify(Event::EVENT_DIEDONSECONDLAYER_POOKA);

		}
		else if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 3)
		{
			// Brown
			Messenger::instance().Notify(Event::EVENT_DIEDONTHIRDLAYER_POOKA);
		}
		else
		{
			// Red
			Messenger::instance().Notify(Event::EVENT_DIEDONFOURTHLAYER_POOKA);
		}

	}
	// check if fygar
	if (m_pParent->GetComponent<FygarComponent>() != nullptr)
	{
		// call event accordingly
		// set it to the right texture
		if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 1)
		{
			// Yellow
			Messenger::instance().Notify(Event::EVENT_DIEDONFIRSTLAYER_FYGAR);

		}
		else if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 2)
		{
			// Orange 
			Messenger::instance().Notify(Event::EVENT_DIEDONSECONDLAYER_FYGAR);

		}
		else if (m_pParent->GetTransform().GetPosition().y < (height / 4) * 3)
		{
			// Brown
			Messenger::instance().Notify(Event::EVENT_DIEDONTHIRDLAYER_FYGAR);
		}
		else
		{
			// Red
			Messenger::instance().Notify(Event::EVENT_DIEDONFOURTHLAYER_FYGAR);
		}

	}
}
