#include "MiniginPCH.h"
#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject * parent, ScoreObserver * scoreObserver)
	:m_pParent(parent)
	,m_ScoreObserver(scoreObserver)
	, m_prevScore(0)
{
}

void dae::ScoreComponent::Update(const float &)
{
	// get the score from the observer,
	int score = m_ScoreObserver->GetScore();
	

	// tell the parents textrenderer what to render
	if (m_prevScore != score)
	{
		m_pParent->GetComponent<TextRendererComponent>()->ChangeText(std::string("SCORE: ") + std::to_string(score));
		m_prevScore = score;
	}

}

void dae::ScoreComponent::Render() const
{
}
