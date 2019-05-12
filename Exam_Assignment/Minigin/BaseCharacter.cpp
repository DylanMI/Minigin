#include "MiniginPCH.h"
#include "BaseCharacter.h"
dae::State dae::BaseCharacter::GetState()
{
	return m_CurrentState;
}

void dae::BaseCharacter::SetState(State newState)
{
	m_CurrentState = newState;
	SDL_log(m_CurrentState);
}

dae::BaseCharacter::~BaseCharacter()
{
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		delete m_pComponents[i];
	}
}
