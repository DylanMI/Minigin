#pragma once
#include "BaseComponent.h"
#include "BaseComponent.h"

#include "TextureComponent.h"
#include "CollisionComponent.h"
#include "DeleteSelfComponent.h"

#include "Structs.h"

class GameObject;
namespace dae
{
	class FygarGunComponent : public BaseComponent
	{
	public:
		explicit FygarGunComponent(GameObject* parent, Scene& scene);
		virtual ~FygarGunComponent() = default;
		FygarGunComponent(const FygarGunComponent& other) = delete;
		FygarGunComponent(FygarGunComponent&& other) = delete;
		FygarGunComponent& operator=(const FygarGunComponent& other) = delete;
		FygarGunComponent& operator=(FygarGunComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		
		void Shoot(Point2f direction);
		bool GetCanShoot();
	private:
		GameObject* m_pParent;
		Scene& m_scene;

		const float m_shootCooldownTime = 0.5f;
		float m_shootCooldownTimer;
		bool m_canShoot;
	};
}
