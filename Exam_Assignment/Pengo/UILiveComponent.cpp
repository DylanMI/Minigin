#include "pch.h"
#include "UILiveComponent.h"

dae::UILiveComponent::UILiveComponent(GameObject * parent, GameObserver * GameObserver)
	: BaseComponent(parent)
	, m_GameObserver (GameObserver)
	, m_prevLives (0)
{
	m_prevLives = m_GameObserver->GetLives();
}

void dae::UILiveComponent::Update(const float & deltaTime)
{
	// get the lives from the observer,
	int lives = m_GameObserver->GetLives();

	// tell the parents textrenderer what to render
	if (m_prevLives != lives)
	{
		m_pParent->GetComponent<TextRendererComponent>()->ChangeText(std::string("LIVES: ") + std::to_string(lives));
		m_prevLives = lives;
	}
}

void dae::UILiveComponent::Render() const
{
}
