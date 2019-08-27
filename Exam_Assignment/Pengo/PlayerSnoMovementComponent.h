#pragma once
#include <BaseComponent.h>
namespace dae
{
	class PlayerSnoMovementComponent : public BaseComponent
	{
	public:
		explicit PlayerSnoMovementComponent(GameObject* parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj, GameObserver * gameObserver);
		virtual ~PlayerSnoMovementComponent();
		PlayerSnoMovementComponent(const PlayerSnoMovementComponent& other) = delete;
		PlayerSnoMovementComponent(PlayerSnoMovementComponent&& other) = delete;
		PlayerSnoMovementComponent& operator=(const PlayerSnoMovementComponent& other) = delete;
		PlayerSnoMovementComponent& operator=(PlayerSnoMovementComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void Move(direction direction);
		void Interact();

		void SetPosition(int idxPos);
		void SetStartIdx(int idxPos);

		void GetCatched(GameObject* Catcher);

		void Die(int ScoreForDeath);

	private:
		GameObject* mp_gameGridObj;
		GameObserver* mp_GameObserver;

		// movement variables
		Point2f m_WidthAndHeight;
		float m_Speed;
		float m_prevSpeed;
		Point2f m_currPos;

		int m_startIdx;

		int m_prevIdx;

		// used for interacting
		int m_lastBumpedIntoIdx = -1;

		const float m_interactCD = 0.5f;
		float m_interactTimer;
		bool m_canInteract;

		GameObject* m_CatchedByThis;

		// used for lerping
		Point2f m_start;
		Point2f m_destination;
		bool m_isTraveling;
		float T;

		// struggling vars
		const float m_struggletime = 2.0f;
		float m_struggleTimer;

		// functions
		Point2f LerpPos(float DT);
	};

}

