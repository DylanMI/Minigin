#include "MiniginPCH.h"
#include "AiComponent.h"

#pragma region AIComponent
dae::AiComponent::AiComponent(GameObject * parent)
	: m_pParent(parent)
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
void dae::AiComponent::AddTransition(GameObject * parent, State goToState, State StartState, std::vector<bool>* prerequisites)
{
	m_transitions.push_back(Transition(parent, goToState, StartState, prerequisites));
}
#pragma endregion AIComponent

#pragma region Transition

dae::Transition::Transition(GameObject * parent, State goToState, State StartState, std::vector<bool>* prerequisites)
	:m_pParent(parent)
	,m_gotoState(goToState)
	,m_StartState(StartState)
	,m_prerequisites(prerequisites)
{
}

dae::Transition::~Transition()
{
	m_pParent = nullptr;
	m_prerequisites = nullptr;
}

bool dae::Transition::Check()
{
	bool checker = true;
	// first check if the state you have to check is actually in play now (StartState)
	if (m_StartState == dynamic_cast<BaseCharacter*>(m_pParent)->GetState())
	{	
		// run trough all the prerequisites, and put the owner to the state it wants to go(goToState)
        // but only if all the prerequisites are met
		for (size_t i{}, s = m_prerequisites->size(); i < s; i++)
		{
			// if there is lag, its due to the ->at() probably
			// and if there is something wrong, it is again due to the -> at() ... never used it before
			if (!m_prerequisites->at(i))
			{
				checker = false;
			}
		}
	}
	else checker = false;
	if (checker)
	{
		dynamic_cast<BaseCharacter*>(m_pParent)->SetState(m_gotoState);
		return true;
	}
	return false;
}
#pragma endregion Transition
