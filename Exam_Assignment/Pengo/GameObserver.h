#pragma once
#include <Observer.h>
#include "Messenger.h"
#include "GameObject.h"
namespace dae
{
	class GameObserver : public Observer
	{
	public:
		GameObserver(GameObject* gameGridObj);
		~GameObserver();
		virtual void Notify(Event eventType, int extraInfo) override;

		int GetScore();
		int GetLives();

		int GetAmmSnoBeeAlive();

	private:
		int m_score;
		int m_lives;

		int m_ammSnoBeeAlive;
		int m_eggCount;

		bool m_isDiamondEventLocked;

		GameObject* mp_gameGridObj;
	};
}




