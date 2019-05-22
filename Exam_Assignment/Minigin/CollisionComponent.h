#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Structs.h"

namespace dae
{
	enum collisionTag
	{
		Terrain,
		Pooka,
		Fugar,
		Player,
		Rock,
		Blowgun,
		Fire,
		Nothing
	};

	class BaseComponent;
	class GameObject;
	class Texture2D;
	
	class CollisionComponent : public BaseComponent
	{
	public:
		explicit CollisionComponent(GameObject* parent);
		virtual ~CollisionComponent() override;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetTag(collisionTag collTag);
		collisionTag GetTag();

		void SetWidthAndHeight(Point2f WidthAndHeight);
		Rectf getBody();

	private:
		Rectf m_collisionBody;
		Point2f m_WidthAndHeight;
		collisionTag m_collTag;
		dae::GameObject* m_pParent;
	};
}

