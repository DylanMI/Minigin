#include "MiniginPCH.h"
#include "BaseCharacter.h"

void dae::BaseCharacter::Update(const float & deltaTime)
{
	// update all the components
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		m_pComponents[i]->Update(deltaTime);
	}
}

void dae::BaseCharacter::Render() const
{
	// legacy
	const auto pos = mTransform.GetPosition();
	// ~legacy

	// render all the components
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		m_pComponents[i]->Render();
	}
}

void dae::BaseCharacter::SetPosition(Point2f pos)
{
	mTransform.SetPosition(pos.x, pos.y, 0.0f);
}

dae::Transform dae::BaseCharacter::GetTransform()
{
	return mTransform;
}

dae::State dae::BaseCharacter::GetState()
{
	return m_CurrentState;
}

void dae::BaseCharacter::SetState(State newState)
{
	m_CurrentState = newState;
}

dae::BaseCharacter::~BaseCharacter()
{
	for (size_t i{}, s = m_pComponents.size(); i < s; i++)
	{
		delete m_pComponents[i];
	}
}
