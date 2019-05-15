#pragma once
#include "BaseCharacter.h"
namespace dae
{
	class PlayerCharacter : public BaseCharacter
	{
	public:
		State GetState() override;
		void SetState(State newState) override;
		float GetSpeed();
		void SetSpeed(float newSpeed);

		void SetBoundaries(Rectf boundry);

		virtual void SetPosition(Point2f pos)override;
		virtual Transform GetTransform()override;

		void Move(Point2f direction, float deltaTime);

		PlayerCharacter() = default;
		virtual ~PlayerCharacter() override;
		PlayerCharacter(const PlayerCharacter& other) = delete;
		PlayerCharacter(PlayerCharacter&& other) = delete;
		PlayerCharacter& operator=(const PlayerCharacter& other) = delete;
		PlayerCharacter& operator=(PlayerCharacter&& other) = delete;

	private:
		// legacy var start
		Transform mTransform;
		// legacy var end

		State m_CurrentState = State::IDLE;
		std::vector<BaseComponent*> m_pComponents;
		float m_speed;
		Rectf m_mapBoundry;

		const int m_charWidth = 16;
		const int m_CharHeight = 16;

	};
}


