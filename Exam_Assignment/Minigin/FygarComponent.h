#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "CollisionCheckerComponent.h"
#include "FygarGunComponent.h"

#include "Structs.h"
#include "Utils.h"

namespace dae
{
	class FygarComponent : public BaseComponent
	{
	public:
		explicit FygarComponent(GameObject* parent);
		virtual ~FygarComponent();
		FygarComponent(const FygarComponent& other) = delete;
		FygarComponent(FygarComponent&& other) = delete;
		FygarComponent& operator=(const FygarComponent& other) = delete;
		FygarComponent& operator=(FygarComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void ShiftDirection();
		void SetTarget(GameObject* newTarget);
		void PutBackAFrame(float deltatime);
		void SetState(State newState);
		State GetState();

		bool* GetToGhostState();
		bool* GetToWanderingState();
		bool* GetToShootState();
		bool* GetIsInflated();
		bool* GetIsNotInflated();
		void SetIsInflated(bool newBool);
		bool* GetIsDead();


		void AddblowCount(int amm);
	private:
		GameObject* m_pParent;
		GameObject* m_Target;

		State m_currentState;

		Point2f m_direction;

		const float m_GhostTime = 5.0f;
		float m_GhostTimer;

		const float m_TimeBeforeCheck = 2.0f;
		float m_CheckTimer;

		const float m_TimeBeforeShooting = 3.0f;
		float m_ShootTimer;

		const float m_TimeBeforeStopShooting = 0.5f;
		float m_stopShootingTimer;

		const float m_DeflateTime = 1.5f;
		float m_DeflateTimer;

		bool* m_ToGhostState;
		bool* m_ToWandering;
		bool* m_IsInflated;
		bool* m_IsNotInflated;
		bool* m_ToFiringState;

		bool* m_IsDead;

		int m_blowCounter;
	};

}

