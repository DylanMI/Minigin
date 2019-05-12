#pragma once
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
	};

	class BaseCharacter : public GameObject
	{
	public:
		void Update(const float& deltaTime) override;
		void Render() const override;
		void SetPosition(Point2f pos) override;
		Transform GetTransform() override;
	
		State GetState();
		void SetState(State newState);

		BaseCharacter() = default;
		~BaseCharacter();
		BaseCharacter(const BaseCharacter& other) = delete;
		BaseCharacter(BaseCharacter&& other) = delete;
		BaseCharacter& operator=(const BaseCharacter& other) = delete;
		BaseCharacter& operator=(BaseCharacter&& other) = delete;

	private:
		// legacy var start
		Transform mTransform;
		// legacy var end

		State m_CurrentState;
		std::vector<BaseComponent*> m_pComponents;

	};

}
