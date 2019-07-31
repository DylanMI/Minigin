#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include <cmath>
namespace dae
{
	class PlayerPengoMovementComponent : public BaseComponent
	{
	public:
		explicit PlayerPengoMovementComponent(GameObject* parent, float Speed);
		virtual ~PlayerPengoMovementComponent();
		PlayerPengoMovementComponent(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent(PlayerPengoMovementComponent&& other) = delete;
		PlayerPengoMovementComponent& operator=(const PlayerPengoMovementComponent& other) = delete;
		PlayerPengoMovementComponent& operator=(PlayerPengoMovementComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	private:

		// variables
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

