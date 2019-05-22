#pragma once
#include <vector>
#include <algorithm>

class Observer;

enum Event
{
	EVENT_DIEDONFIRSTLAYER,
	EVENT_DIEDONSECONDLAYER,
	EVENT_DIEDONTHIRDLAYER,
	EVENT_DIEDONFOURTHLAYER,
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



