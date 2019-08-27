#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "GameFieldGridComponent.h"

#include <cmath>
namespace dae
{
	enum direction
	{
		LEFT,RIGHT,UP,DOWN,NONE

	};

	class PlayerPengoMovementComponent : public BaseComponent
	{
	public:
		explicit PlayerPengoMovementComponent(GameObject* parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj, GameObserver * gameObserver);
		virtual ~PlayerPengoMovementComponent();
		PlayerPengoMovementComponent(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent(PlayerPengoMovementComponent&& other) = delete;
		PlayerPengoMovementComponent& operator=(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent& operator=(PlayerPengoMovementComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void Move(direction direction);
		void Interact();
		
		void SetPosition(int idxPos);
		void SetStartIdx(int idxPos);
	private:

		GameObject* mp_gameGridObj;
		GameObserver* mp_GameObserver;

		// movement variables
		Point2f m_WidthAndHeight;
		float m_Speed;
		Point2f m_currPos;
		
		int m_startIdx;
		
		// used for interacting
		int m_lastBumpedIntoIdx = -1;

		const float m_interactCD = 0.5f;
		float m_interactTimer;
		bool m_canInteract;

		// used for lerping
		Point2f m_start;
		Point2f m_destination;
		bool m_isTraveling;
		float T;

		// functions
		Point2f LerpPos(float DT);

		void StunBees(direction dir, int ammPointsW, int ammPointsH);
	};

}

