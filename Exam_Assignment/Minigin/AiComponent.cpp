#include "MiniginPCH.h"
#include "AiComponent.h"

#pragma region AIComponent
dae::AiComponent::AiComponent(GameObject * parent)
	: BaseComponent(parent)
{
}

dae::AiComponent::~AiComponent()
{
	m_pParent = nullptr;
	delete m_pParent;
}
void dae::AiComponent::Update(const float & )
{
	// check all the prerequisites
	for (size_t i{}, s = m_transitions.size(); i < s; i++)
	{
		if (m_transitions[i].Check()) return;
	}
}

void dae::AiComponent::Render() const
{
	// do anothing
}
void dae::AiComponent::AddTransition(GameObject * parent, State goToState, State StartState, std::vector<bool*> prerequisites)
{
	m_transitions.push_back(Transition(parent, goToState, StartState, prerequisites));
}
#pragma endregion AIComponent

#pragma region Transition

dae::Transition::Transition(GameObject * parent, State goToState, State StartState, std::vector<bool*> prerequisites)
	:m_pParent(parent)
	,m_gotoState(goToState)
	,m_StartState(StartState)
	,m_prerequisites(prerequisites)
{
}

dae::Transition::~Transition()
{
	m_pParent = nullptr;
	/*m_prerequisites = nullptr;*/
}

bool dae::Transition::Check()
{
	// check if the parent is a pooka
	if (m_pParent->GetComponent<PookaComponent>() != nullptr)
	{
		bool checker = true;
		// first check if the state you have to check is actually in play now (StartState)
		if (m_StartState == m_pParent->GetComponent<PookaComponent>()->GetState())
		{
			// run trough all the prerequisites, and put the owner to the state it wants to go(goToState)
			// but only if all the prerequisites are met
			for (size_t i{}, s = m_prerequisites.size(); i < s; i++)
			{
				if (!*m_prerequisites[i])
				{
					checker = false;
				}
			}
		}
		else checker = false;
		if (checker)
		{
			m_pParent->GetComponent<PookaComponent>()->SetState(m_gotoState);
			return true;
		}
		return false;
	}
	// else check if its a fygar
	else if (m_pParent->GetComponent<FygarComponent>() != nullptr)
	{
		bool checker = true;
		// first check if the state you have to check is actually in play now (StartState)
		if (m_StartState == m_pParent->GetComponent<FygarComponent>()->GetState())
		{
			// run trough all the prerequisites, and put the owner to the state it wants to go(goToState)
			// but only if all the prerequisites are met
			for (size_t i{}, s = m_prerequisites.size(); i < s; i++)
			{
				if (!*m_prerequisites[i])
				{
					checker = false;
				}
			}
		}
		else checker = false;
		if (checker)
		{
			m_pParent->GetComponent<FygarComponent>()->SetState(m_gotoState);
			return true;
		}
		return false;
	}

	//else just do the normal one
	else
	{
		bool checker = true;
		// first check if the state you have to check is actually in play now (StartState)
		if (m_StartState == m_pParent->GetComponent<StateComponent>()->GetState())
		{
			// run trough all the prerequisites, and put the owner to the state it wants to go(goToState)
			// but only if all the prerequisites are met
			for (size_t i{}, s = m_prerequisites.size(); i < s; i++)
			{
				if (!*m_prerequisites[i])
				{
					checker = false;
				}
			}
		}
		else checker = false;
		if (checker)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(m_gotoState);
			return true;
		}
		return false;
	}
	
}
#pragma endregion Transition
