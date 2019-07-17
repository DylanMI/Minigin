#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "Command.h"
#include <map>
#include "Structs.h"
#include "Utils.h"

class CollisionCommand;
class GameObject;
namespace dae
{
	class CollisionCheckerComponent : public BaseComponent
	{
	public:
		explicit CollisionCheckerComponent(GameObject* parent);
		virtual ~CollisionCheckerComponent();
		CollisionCheckerComponent(const CollisionCheckerComponent& other) = delete;
		CollisionCheckerComponent(CollisionCheckerComponent&& other) = delete;
		CollisionCheckerComponent& operator=(const CollisionCheckerComponent& other) = delete;
		CollisionCheckerComponent& operator=(CollisionCheckerComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		collisionTag Peek(Point2f Offset, Point2f widthAndHeight);

		void SetWidthAndHeightBody(Point2f newWidthAndHeigh);
		void SetOffset(Point2f newOffset);
		void addCollisionEvent(CollisionCommand* EventExecution, collisionTag tag);

		void SetDisabled(bool isDisabled);

	private:
		std::map<collisionTag, CollisionCommand* > collisionEventMap;
		Rectf m_collisionBody{};
		
		Point2f m_widthAndHeight;
		Point2f m_offset;

		bool m_isDisabled;
	};

}
