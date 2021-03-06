#pragma once
#include <BaseComponent.h>
namespace dae
{

	class SnoBeeAIComponent : public BaseComponent
	{
	public:
		explicit SnoBeeAIComponent(GameObject* parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj);
		virtual ~SnoBeeAIComponent();
		SnoBeeAIComponent(const SnoBeeAIComponent& other) = delete;
		SnoBeeAIComponent(SnoBeeAIComponent&& other) = delete;
		SnoBeeAIComponent& operator=(const SnoBeeAIComponent& other) = delete;
		SnoBeeAIComponent& operator=(SnoBeeAIComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetPosition(int idxPos);
		void GetCatched(GameObject* Catcher);

		void Die(int ScoreForDeath);
	private:

		GameObject* mp_gameGridObj;

		// movement variables
		Point2f m_WidthAndHeight;
		float m_Speed;
		float m_prevSpeed;
		Point2f m_currPos;

		int m_prevIdx;

		bool m_IsDigging;

		GameObject* m_CatchedByThis;

		// struggling vars
		const float m_struggletime = 2.0f;
		float m_struggleTimer;


		// used for lerping
		Point2f m_start;
		Point2f m_destination;
		bool m_isTraveling;
		float T;

		// functions

		
		Point2f LerpPos(float DT);
	};


}
