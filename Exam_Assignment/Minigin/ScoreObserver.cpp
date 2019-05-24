#include "MiniginPCH.h"
#include "ScoreObserver.h"


ScoreObserver::ScoreObserver()
{
}


ScoreObserver::~ScoreObserver()
{
}

void ScoreObserver::Notify(Event eventType)
{
	switch (eventType)
	{
		case Event::EVENT_DIEDONFIRSTLAYER_POOKA:
			m_Score += m_FirstLayerScoreReward_POOKA;
			break;
		case Event::EVENT_DIEDONSECONDLAYER_POOKA:
			m_Score += m_SecondLayerScoreReward_POOKA;
			break;
		case Event::EVENT_DIEDONTHIRDLAYER_POOKA:
			m_Score += m_ThirdLayerScoreReward_POOKA;
			break;
		case Event::EVENT_DIEDONFOURTHLAYER_POOKA:
			m_Score += m_FourthLayerScoreReward_POOKA;
			break;

		case Event::EVENT_DIEDONFIRSTLAYER_FYGAR:
			m_Score += m_FirstLayerScoreReward_FYGAR;
			break;
		case Event::EVENT_DIEDONSECONDLAYER_FYGAR:
			m_Score += m_SecondLayerScoreReward_FYGAR;
			break;
		case Event::EVENT_DIEDONTHIRDLAYER_FYGAR:
			m_Score += m_ThirdLayerScoreReward_FYGAR;
			break;
		case Event::EVENT_DIEDONFOURTHLAYER_FYGAR:
			m_Score += m_FourthLayerScoreReward_FYGAR;
			break;
	}
}

int ScoreObserver::GetScore()
{
	return m_Score;
}

void ScoreObserver::Reset()
{
	m_Score = 0;
}
