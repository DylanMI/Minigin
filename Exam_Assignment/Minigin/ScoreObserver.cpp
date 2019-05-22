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
		case Event::EVENT_DIEDONFIRSTLAYER:
			m_Score += m_FirstLayerScoreReward;
			break;
		case Event::EVENT_DIEDONSECONDLAYER:
			m_Score += m_SecondLayerScoreReward;
			break;
		case Event::EVENT_DIEDONTHIRDLAYER:
			m_Score += m_ThirdLayerScoreReward;
			break;
		case Event::EVENT_DIEDONFOURTHLAYER:
			m_Score += m_FourthLayerScoreReward;
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
