#include "MiniginPCH.h"
#include "ClampComponent.h"


dae::ClampComponent::ClampComponent(GameObject * parent)
	:m_pParent(parent)
{}

void dae::ClampComponent::Update(const float & )
{
}

void dae::ClampComponent::Render() const
{
}

void dae::ClampComponent::SetClampRect(Rectf newRect)
{
	m_ClampRect = newRect;
}

bool dae::ClampComponent::CheckClamp(Point2f position, Point2f WidthAndHeight)
{
	if (position.x < m_ClampRect.x || position.y < m_ClampRect.y || position.x + WidthAndHeight.x > m_ClampRect.x + m_ClampRect.w || position.y + WidthAndHeight.y > m_ClampRect.y + m_ClampRect.h)
	{
		// check if its an enemy
		if (m_pParent->GetComponent<PookaComponent>() != nullptr)
		{
			m_pParent->GetComponent<PookaComponent>()->ShiftDirection();

		}
		if (m_pParent->GetComponent<FygarComponent>() != nullptr)
		{
			m_pParent->GetComponent<FygarComponent>()->ShiftDirection();
		}


		// else just return false
		return false;


	}

	return true;
}
