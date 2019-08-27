#include "pch.h"
#include "GameObserver.h"

dae::GameObserver::GameObserver(GameObject * gameGridObj)
	: m_lives { 3 }
	, m_score { 0 }
	, m_ammSnoBeeAlive { 0 }
	, m_eggCount { 0 }
	, m_isDiamondEventLocked {false}
	, mp_gameGridObj{gameGridObj}
{
	
}

dae::GameObserver::~GameObserver()
{
}

void dae::GameObserver::Notify(Event eventType, int extraInfo)
{

	switch (eventType)
	{
	case Event::EVENT_PENGODIED:
		// reduce lifes
		m_lives--;
		break;
	case Event::EVENT_ENEMYDIED:
		// award points according to extraInfo
		m_score += extraInfo;
		// tell the next egg to hatch
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->GetAmmEggsLeft() > 0)
		{
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->HatchNextEgg();
			// keep an egg tally
			m_eggCount--;
		}
		// keep a sno bee tally
		m_ammSnoBeeAlive--;

		break;
	case Event::EVENT_ENEMYSPAWNED:
		
		// keep count of how many sno bees there are
		m_ammSnoBeeAlive++;

		break;
	case Event::EVENT_EGGSPAWNED:

		// keep count of how many eggs there are
		m_eggCount++;

		break;
	case Event::EVENT_EGGDESTROYED:
		// for itself
		m_eggCount--;

		break;
	case Event::EVENT_DIAMONDSCHAIN:
		// check if it occured yet
		if (m_isDiamondEventLocked) return;
		
		
		// award points, and lock this event untill reset
		m_isDiamondEventLocked = true;
		m_score += 2000;
		break;
	case Event::EVENT_ENDGAME:

		break;


	default:
		break;
	}

}

int dae::GameObserver::GetScore()
{
	return m_score;
}

int dae::GameObserver::GetLives()
{
	return m_lives;
}

int dae::GameObserver::GetEggCount()
{
	return m_eggCount;
}

int dae::GameObserver::GetAmmSnoBeeAlive()
{
	return m_ammSnoBeeAlive;
}
