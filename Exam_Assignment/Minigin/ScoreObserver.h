#pragma once
#include "Observer.h"
#include "Messenger.h"

class ScoreObserver : public Observer
{
public:
	ScoreObserver();
	~ScoreObserver();

	virtual void Notify(Event eventType) override;

	int GetScore();
	void Reset();
	


private:
	int m_Score{ 0 };

	const int m_FirstLayerScoreReward{ 100 };
	const int m_SecondLayerScoreReward{ 200 };
	const int m_ThirdLayerScoreReward{ 500 };
	const int m_FourthLayerScoreReward{ 1000 };
};

