#pragma once
#include "Messenger.h"

class Observer
{
public:
	virtual ~Observer() {}
	virtual void Notify(Event eventType, int extraInfo) = 0;
};
