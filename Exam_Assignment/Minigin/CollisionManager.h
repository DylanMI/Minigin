#pragma once

#include "Singleton.h"
#include <vector>
#include "GameObject.h"
#include <algorithm>
class GameObject;
namespace dae
{
	class CollisionManager : public Singleton<CollisionManager>
	{
	public:
		CollisionManager() = default;
		~CollisionManager() = default;

		void RegisterCollisionObject(GameObject* object)
		{
			m_collisionObjects.push_back(object);
		}
		void RemoveCollisionObject(GameObject* object)
		{
			m_collisionObjects.erase(std::remove(m_collisionObjects.begin(), m_collisionObjects.end(), object), m_collisionObjects.end());
		}

		std::vector<GameObject*> GetCollisionObjects()
		{
			return m_collisionObjects;
		}

	private:
		std::vector<GameObject*> m_collisionObjects;
	};
}
