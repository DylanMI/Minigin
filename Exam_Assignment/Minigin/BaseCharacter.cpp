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

void dae::BaseCharacter::SetPosition(Point2f pos)
{
	mTransform.SetPosition(pos.x, pos.y, 0.0f);
}

dae::Transform dae::BaseCharacter::GetTransform()
{
	return mTransform;
}

dae::BaseCharacter::~BaseCharacter()
{
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		delete m_pComponents[i];
	}
}
