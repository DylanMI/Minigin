#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

#include "GameObject.h"

#include "DeleteSelfComponent.h"

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
		void SetIsFalling(bool isFalling);
		void SetIsBreaking(bool isBreaking);

		void AddVictim(GameObject* newVictim);
		bool IsVictimAlreadyRegistered(GameObject* Victim);

		bool GetIsFalling();
		bool GetIsBreaking();


	private:
		GameObject* m_pParent;

		std::vector<GameObject*> m_victims;

		float m_fallSpeed;

		bool m_isFalling;
		
		bool m_isBreaking;
		bool m_isActuallyFalling;
		float m_breakTimer;

		const float m_fallTime = 0.5f;
		float m_fallTimer;

	};

}

