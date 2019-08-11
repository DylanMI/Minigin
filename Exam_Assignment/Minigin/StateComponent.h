#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	enum State
	{
		// general
		FACING_LEFT,
		FACING_RIGHT,
		FACING_UP,
		FACING_DOWN,
		
		DIGGING_LEFT,
		DIGGING_RIGHT,
		DIGGING_UP,
		DIGGING_DOWN,

		IDLE,
		// player

		// AI
		STRUGGLING,


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
		bool GetIsPlayer();


	private:
		State m_CurrentState = State::FACING_DOWN;

		bool m_isPlayer;
	};

}

