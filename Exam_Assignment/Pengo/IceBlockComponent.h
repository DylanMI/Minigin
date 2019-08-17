#pragma once
#include <BaseComponent.h>

#include "GameObject.h"
#include "GameFieldGridComponent.h"

#include <cmath>
namespace dae
{
	class IceBlockComponent : public BaseComponent
	{
	public:
		explicit IceBlockComponent(GameObject* parent,Point2f WidthAndHeight,GameObject * gameGridObj);
		virtual ~IceBlockComponent();
		IceBlockComponent(const IceBlockComponent& other) = delete;
		IceBlockComponent(IceBlockComponent&& other) = delete;
		IceBlockComponent& operator=(const IceBlockComponent& other) = delete;
		IceBlockComponent& operator=(IceBlockComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetPosition(int idxPos);

		void SetSpeed(float newSpeed);
		bool StartGliding(direction glidingDirection);
		void StopGliding();
		void StartBreaking(float speedOfBreak);

		bool GetIsSliding();

		Point2f getCurrPos();
		Point2f getWidthnHeight();

	private:
		direction m_glidingDirection;
		bool m_isGliding;
		GameObject * mp_gameGridObj;
		
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

