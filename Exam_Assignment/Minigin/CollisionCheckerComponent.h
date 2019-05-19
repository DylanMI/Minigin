#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "Command.h"
#include <map>
#include "Structs.h"

class GameObject;
namespace dae
{
	class CollisionCheckerComponent : public BaseComponent
	{
	public:
		explicit CollisionCheckerComponent(GameObject* parent);
		virtual ~CollisionCheckerComponent() = default;
		CollisionCheckerComponent(const CollisionCheckerComponent& other) = delete;
		CollisionCheckerComponent(CollisionCheckerComponent&& other) = delete;
		CollisionCheckerComponent& operator=(const CollisionCheckerComponent& other) = delete;
		CollisionCheckerComponent& operator=(CollisionCheckerComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetWidthAndHeightBody(Point2f newWidthAndHeigh);
		void addCollisionEvent(Command* EventExecution, collisionTag tag);

	private:
		GameObject* m_pParent;
		std::map<collisionTag, CollisionCommand* > collisionEventMap{};
		Rectf m_collisionBody{};
		Point2f m_widthAndHeight{};
	};

}
