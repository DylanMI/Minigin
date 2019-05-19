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
		SHOOTING,
		DEAD,
		ANY
	};

	class GameObject;
	class StateComponent : public BaseComponent
	{
	public:
		explicit StateComponent(GameObject* parent);
		virtual ~StateComponent() = default;
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		State GetState();
		void SetState(State newState);

	private:
		GameObject* m_pParent;
		State m_CurrentState = State::IDLE;
	};

}

