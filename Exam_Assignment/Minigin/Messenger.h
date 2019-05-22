#pragma once
#include <vector>
#include <algorithm>

class Observer;

enum Event
{
	EVENT_DIEDONFIRSTLAYER_POOKA,
	EVENT_DIEDONSECONDLAYER_POOKA,
	EVENT_DIEDONTHIRDLAYER_POOKA,
	EVENT_DIEDONFOURTHLAYER_POOKA,

	EVENT_DIEDONFIRSTLAYER_FYGAR,
	EVENT_DIEDONSECONDLAYER_FYGAR,
	EVENT_DIEDONTHIRDLAYER_FYGAR,
	EVENT_DIEDONFOURTHLAYER_FYGAR,

	EVENT_ROCKKILLED_ONE,
	EVENT_ROCKKILLED_TWO,
	EVENT_ROCKKILLED_THREE,
	EVENT_ROCKKILLED_FOUR,
	EVENT_ROCKKILLED_FIVE,
	EVENT_ROCKKILLED_SIX,
	EVENT_ROCKKILLED_SEVEN,
	EVENT_ROCKKILLED_EIGHT,

	EVENT_DIED
};


struct Subscription
{
	Observer *client;
	Event eventType;

	bool operator==(Subscription right) const
	{
		bool Ret = this->client == right.client && this->eventType == right.eventType;
		return Ret;
	}

	Subscription& operator=(Subscription const& o)
	{
		if (&o != this)
		{
			client = o.client;
			eventType = o.eventType;
		}
		return *this;
	}
};

class Messenger
{
public:
	static Messenger& instance()
	{
		static Messenger *instance = new Messenger();
		return *instance;
	}

private:
	Messenger() {}
	// Functions and members //

public:

	void Notify(Event eventType);
	void Subscribe(Observer* observer, Event eventType);
	void UnSubscribe(Observer* observer, Event eventType);

private:
	std::vector<Subscription> m_Subscriptions;

};



