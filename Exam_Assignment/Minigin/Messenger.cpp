#include "MiniginPCH.h"
#include "Messenger.h"
#include "Observer.h"

void Messenger::Notify(Event eventType, int extraInfo)
{
	for (size_t i{}, s = m_Subscriptions.size(); i < s; i++)
	{
		if (m_Subscriptions[i].eventType == eventType) m_Subscriptions[i].client->Notify(eventType, extraInfo);
	}
}

void Messenger::Subscribe(Observer* observer, Event eventType)
{
	// TODO: check if that subscription already exists, if yes then don't add it
	m_Subscriptions.push_back(Subscription{ observer,eventType });
}

void Messenger::UnSubscribe(Observer* observer, Event eventType)
{

	// find the one to delete
	for (size_t i{}, s = m_Subscriptions.size(); i < s; i++)
	{
		// if its the same delete it
		if (m_Subscriptions[i] == Subscription{ observer,eventType })
		{
			m_Subscriptions.erase(m_Subscriptions.begin() + i);
			return;
		}
	}

}
