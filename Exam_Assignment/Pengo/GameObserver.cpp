#include "pch.h"
#include "GameObserver.h"

GameObserver::GameObserver(GameObject * gameGridObj)
	: m_lives { 3 }
	, m_score { 0 }
	, m_ammSnoBeeAlive { 0 }
	, m_isDiamondEventLocked {false}
{
}

GameObserver::~GameObserver()
{
}

void GameObserver::Notify(Event eventType, int extraInfo)
{

	switch (eventType)
	{
	case Event::EVENT_PENGODIED:
		// reduce lifes

			break;
	case Event::EVENT_ENEMYDIED:
		// award points according to extraInfo

		// tell the next egg to hatch

		// keep count of how many sno bees there are

		break;
	case Event::EVENT_ENEMYSPAWNED:
		
		// keep count of how many sno bees there are


		break;
	case Event::EVENT_DIAMONDSCHAIN:
		// check if it occured yet
		if (m_isDiamondEventLocked) return;
		
		
		// award points, and lock this event untill reset

		m_isDiamondEventLocked = true;

		break;
	case Event::EVENT_ENDGAME:

		break;


	default:
		break;
	}

}

int GameObserver::GetScore()
{
	return m_score;
}

int GameObserver::GetLives()
{
	return m_lives;
}

int GameObserver::GetAmmSnoBeeAlive()
{
	return m_ammSnoBeeAlive;
}
