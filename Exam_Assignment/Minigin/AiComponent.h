#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "BaseCharacter.h" // will need to add an AI character
#include <map>

class GameObject;

namespace dae
{
#pragma region transition
	// a transition will get check the transitions of the parent[it has a pointer], once all of them are true,
	//it will set the state of the parent to the gotostate

	class Transition
	{
	public:
		Transition(GameObject* parent, State goToState, State StartState, std::vector<bool>* prerequisites);
		~Transition();
		bool Check();
	private:
		GameObject* m_pParent;
		State m_gotoState;	
		State m_StartState;
		std::vector<bool>* m_prerequisites;
	};
#pragma endregion transition

#pragma region AIComponent
	class AiComponent : public BaseComponent
	{
	public:
		explicit AiComponent(GameObject* parent);
		virtual ~AiComponent() override;
		AiComponent(const AiComponent& other) = delete;
		AiComponent(AiComponent&& other) = delete;
		AiComponent& operator=(const AiComponent& other) = delete;
		AiComponent& operator=(AiComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void AddTransition(GameObject* parent, State goToState, State endState, std::vector<bool>* prerequisites);
	private:
		GameObject* m_pParent;
		std::vector<Transition> m_transitions;
	};
#pragma endregion AIComponent
}

