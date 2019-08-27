#include "pch.h"
#include "GameObserver.h"

dae::GameObserver::GameObserver(GameObject * gameGridObj, Scene& parentScene)
	: m_lives { 3 }
	, m_score { m_Standardscore }
	, m_ammSnoBeeAlive { m_StandardammSnoBeeAlive }
	, m_eggCount { m_StandardeggCount }
	, m_isDiamondEventLocked {false}
	, mp_gameGridObj{gameGridObj}
	, m_parentScene{ parentScene }
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

		// clear scene
		m_parentScene.ClearAll();

		// tell the parentscene what to tell the game to load next
		m_parentScene.SetLevelIdx(2);

		// reset yourself
		m_eggCount = m_StandardeggCount;
		m_lives = m_Standardlives;
		m_score = m_Standardscore;
		m_ammSnoBeeAlive = m_StandardammSnoBeeAlive;
		
		break;

	case Event::EVENT_STARTSINGLEPLAYER:
		m_parentScene.ClearAll();
		m_parentScene.SetLevelIdx(1);
		break;

	case Event::EVENT_STARTCOOP:
		m_parentScene.ClearAll();
		m_parentScene.SetLevelIdx(3);
		break;

	case Event::EVENT_STARTVS:
		m_parentScene.ClearAll();
		m_parentScene.SetLevelIdx(5);
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

void dae::GameObserver::AssignGrid(GameObject * gameGridObj)
{
	mp_gameGridObj = gameGridObj;
}


int dae::GameObserver::GetAmmSnoBeeAlive()
{
	return m_ammSnoBeeAlive;
}
