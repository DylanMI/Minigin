#pragma once
#include <vector>
#include <algorithm>

class Observer;

enum Event
{
	EVENT_PENGODIED,
	EVENT_ENEMYSPAWNED,
	EVENT_ENEMYDIED,
	EVENT_EGGSPAWNED,
	EVENT_EGGHATCHED,
	EVENT_EGGDESTROYED,
	EVENT_DIAMONDSCHAIN,
	EVENT_ENDGAME,

	EVENT_STARTSINGLEPLAYER,
	EVENT_STARTCOOP,
	EVENT_STARTVS,

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
	static Messenger& GetInstance()
	{
		static Messenger instance{};
		return instance;
	}

private:
	Messenger() {}
	// Functions and members //

public:

	void Notify(Event eventType, int extraInfo);
	void Subscribe(Observer* observer, Event eventType);
	void UnSubscribe(Observer* observer, Event eventType);

private:
	std::vector<Subscription> m_Subscriptions;

};



