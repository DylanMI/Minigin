#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	enum State
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		IDLE,
		WANDERING,
		GHOSTING,
		SHOOTING,
		DEAD,
		BREAK,
		BREAK_1,
		BREAK_2,
		BLOW_1,
		BLOW_2,
		BLOW_3,
		BLOW_4,
		CAUGHTBYROCK,
		ANY,
	};

	class GameObject;
	class StateComponent : public BaseComponent
	{
	public:
		explicit StateComponent(GameObject* parent, bool isDigDug);
		virtual ~StateComponent() = default;
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		State GetState();
		void SetState(State newState);
		bool GetIsDigDug();


	private:
		GameObject* m_pParent;
		State m_CurrentState = State::IDLE;

		bool m_isDigDug;
	};

}

