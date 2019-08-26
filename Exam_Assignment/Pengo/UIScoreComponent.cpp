#include "pch.h"
#include "UIScoreComponent.h"

dae::UIScoreComponent::UIScoreComponent(GameObject * parent, GameObserver * GameObserver)
	: BaseComponent(parent)
	, m_GameObserver(GameObserver)
	, m_prevScore(0)
{

}

void dae::UIScoreComponent::Update(const float & deltaTime)
{
	// get the score from the observer,
	int score = m_GameObserver->GetScore();

	// tell the parents textrenderer what to render
	if (m_prevScore != score)
	{
		m_pParent->GetComponent<TextRendererComponent>()->ChangeText(std::string("SCORE: ") + std::to_string(score));
		m_prevScore = score;
	}
}

void dae::UIScoreComponent::Render() const
{
}
