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


	private:
		GameObject* m_pParent;
		GameObject* m_Target;

		State m_currentState;
		
		Point2f m_direction;

		const float m_GhostTime = 5.0f;
		float m_GhostTimer;

		const float m_TimeBeforeCheck = 2.0f;
		float m_CheckTimer;

		bool* m_ToGhostState;
		bool* m_ToWandering;
	};


}
