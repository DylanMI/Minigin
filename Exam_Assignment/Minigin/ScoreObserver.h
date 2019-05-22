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

	const int m_FirstLayerScoreReward_POOKA{ 200 };
	const int m_SecondLayerScoreReward_POOKA{ 300 };
	const int m_ThirdLayerScoreReward_POOKA{ 400 };
	const int m_FourthLayerScoreReward_POOKA{ 500 };
};

