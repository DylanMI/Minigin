#pragma once
#include "Observer.h"
#include "Messenger.h"

class LifeObserver : public Observer
{
public:
	LifeObserver();
	~LifeObserver();
	virtual void Notify(Event eventType) override;

	int GetLives();
	bool GetIsDead();
	void Reset();

private:
	int m_lives{ 3 };
	bool m_isDead{ false };
};

