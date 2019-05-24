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
	if (position.x < m_ClampRect.x) return false;
	if (position.y < m_ClampRect.y) return false;
	if (position.x + WidthAndHeight.x > m_ClampRect.x + m_ClampRect.w) return false;
	if (position.y + WidthAndHeight.y > m_ClampRect.y + m_ClampRect.h) return false;
	return true;
}
