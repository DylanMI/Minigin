#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

#include "TextureComponent.h"
#include "CollisionComponent.h"
#include "DeleteSelfComponent.h"

namespace dae
{
	class GameObject;
	class GunComponent : public BaseComponent
	{
	public:
		explicit GunComponent(GameObject* parent, Scene& scene);
		virtual ~GunComponent() = default;
		GunComponent(const GunComponent& other) = delete;
		GunComponent(GunComponent&& other) = delete;
		GunComponent& operator=(const GunComponent& other) = delete;
		GunComponent& operator=(GunComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void Shoot();
		bool GetCanShoot();

	private:
		GameObject* m_pParent;
		Scene& m_scene;

		const float m_shootCooldownTime = 0.5f; 
		float m_shootCooldownTimer;
		bool m_canShoot;
	};

}
