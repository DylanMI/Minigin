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
		explicit PlayerPengoMovementComponent(GameObject* parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj);
		virtual ~PlayerPengoMovementComponent();
		PlayerPengoMovementComponent(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent(PlayerPengoMovementComponent&& other) = delete;
		PlayerPengoMovementComponent& operator=(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent& operator=(PlayerPengoMovementComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void Move(direction direction);
		void SetPosition(int idxPos);

	private:

		GameObject* m_gameGridObj;

		// movement variables
		Point2f m_WidthAndHeight;
		float m_Speed;
		Point2f m_currPos;
		
		// used for lerping
		Point2f m_start;
		Point2f m_destination;
		bool m_isTraveling;
		float T;

		// functions
		Point2f LerpPos(float DT);
	};

}

