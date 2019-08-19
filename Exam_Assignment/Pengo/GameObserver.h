#pragma once
#include <Observer.h>
#include "Messenger.h"

class GameObserver : public Observer
{
public:
	GameObserver();
	~GameObserver();
	virtual void Notify(Event eventType, int extraInfo) override;
};

