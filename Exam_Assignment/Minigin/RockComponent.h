#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class RockComponent : public BaseComponent
	{
	public:
		explicit RockComponent(GameObject* parent);
		virtual ~RockComponent() = default;
		RockComponent(const RockComponent& other) = delete;
		RockComponent(RockComponent&& other) = delete;
		RockComponent& operator=(const RockComponent& other) = delete;
		RockComponent& operator=(RockComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetFallSpeed(float newSpeed);
		void SetIsFalling();
		void Break();

	private:
		GameObject* m_pParent;
		float m_fallSpeed;

		bool m_isFalling;
		bool m_isBreaking;
	};

}

