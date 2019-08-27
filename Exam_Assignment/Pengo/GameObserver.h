#pragma once
#include <Observer.h>
#include "Messenger.h"
#include "GameObject.h"
namespace dae
{
	class GameObserver : public Observer
	{
	public:
		GameObserver(GameObject* gameGridObj, Scene& parentScene);
		~GameObserver();
		virtual void Notify(Event eventType, int extraInfo) override;

		int GetScore();
		int GetLives();
		int GetEggCount();

		void AssignGrid(GameObject* gameGridObj);

		int GetAmmSnoBeeAlive();

		bool GetCloseGame();

	private:
		int m_score;
		int m_lives;
		int m_ammSnoBeeAlive;
		int m_eggCount;

		int m_currLevel;

		const int m_Standardscore{ 0 };
		const int m_Standardlives{ 3 };
		const int m_StandardammSnoBeeAlive{ 0 };
		const int m_StandardeggCount{ 0 };

		bool m_isDiamondEventLocked;
		bool m_CloseGame;

		GameObject* mp_gameGridObj;
		Scene& m_parentScene;
	};
}




