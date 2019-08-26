#include "pch.h"
#include "UIEggComponent.h"

dae::UIEggComponent::UIEggComponent(GameObject * parent, GameObserver * GameObserver)
	:BaseComponent(parent)
	, m_GameObserver(GameObserver)
	, m_prevEggs (0)
{
	m_prevEggs = m_GameObserver->GetEggCount();
}

void dae::UIEggComponent::Update(const float & deltaTime)
{
	// get the score from the observer,
	int eggs = m_GameObserver->GetEggCount();

	// tell the parents textrenderer what to render
	if (m_prevEggs != eggs)
	{
		m_pParent->GetComponent<TextRendererComponent>()->ChangeText(std::string("EGGS: ") + std::to_string(eggs));
		m_prevEggs = eggs;
	}
}

void dae::UIEggComponent::Render() const
{
}
