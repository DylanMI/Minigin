#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "CollisionCheckerComponent.h"

#include "Structs.h"
#include "Utils.h"


namespace dae
{
	class GameObject;
	class PookaComponent : public BaseComponent
	{
	public:
		explicit PookaComponent(GameObject* parent);
		virtual ~PookaComponent();
		PookaComponent(const PookaComponent& other) = delete;
		PookaComponent(PookaComponent&& other) = delete;
		PookaComponent& operator=(const PookaComponent& other) = delete;
		PookaComponent& operator=(PookaComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void ShiftDirection();
		void PutBackAFrame(float deltatime);
		void SetTarget(GameObject* newTarget);
		
		void SetState(State newState);
		State GetState();

		bool* GetToGhostState();
		bool* GetToWanderingState();
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

		const float m_DeflateTime = 1.5f;
		float m_DeflateTimer;

		bool* m_ToGhostState;
		bool* m_ToWandering;
		bool* m_IsInflated;
		bool* m_IsNotInflated;

		bool* m_IsDead;

		int m_blowCounter;
	};


}
