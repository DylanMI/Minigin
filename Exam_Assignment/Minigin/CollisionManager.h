#pragma once

#include "Singleton.h"
#include <vector>
#include "GameObject.h"

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
		std::vector<GameObject*> GetCollisionObjects()
		{
			return m_collisionObjects;
		}

	private:
		std::vector<GameObject*> m_collisionObjects;
	};
}
