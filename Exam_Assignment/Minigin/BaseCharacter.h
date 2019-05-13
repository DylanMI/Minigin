#pragma once
#include <memory>

#include "GameObject.h"
#include "BaseComponent.h"
#include "FPSComponent.h"
#include "TextRendererComponent.h"

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
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
		State GetState();
		void SetState(State newState);

		BaseCharacter() = default;
		virtual ~BaseCharacter() override;
		BaseCharacter(const BaseCharacter& other) = delete;
		BaseCharacter(BaseCharacter&& other) = delete;
		BaseCharacter& operator=(const BaseCharacter& other) = delete;
		BaseCharacter& operator=(BaseCharacter&& other) = delete;

	private:
		// legacy var start
		Transform mTransform;
		// legacy var end

		State m_CurrentState = State::IDLE;
		std::vector<BaseComponent*> m_pComponents;

	};

}
