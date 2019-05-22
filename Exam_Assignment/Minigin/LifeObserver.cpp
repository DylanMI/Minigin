#include "MiniginPCH.h"
#include "LifeObserver.h"


LifeObserver::LifeObserver()
{
}


LifeObserver::~LifeObserver()
{
}

void LifeObserver::Notify(Event eventType)
{
	switch (eventType)
	{
	case Event::EVENT_DIED:
		m_lives--;
		if (m_lives <= 0)
		{
			m_isDead = true;
		}
		break;
	}
}

int LifeObserver::GetLives()
{
	return m_lives;
}

bool LifeObserver::GetIsDead()
{
	return m_isDead;
}

void LifeObserver::Reset()
{
	m_lives = 3;
	m_isDead = false;
}
