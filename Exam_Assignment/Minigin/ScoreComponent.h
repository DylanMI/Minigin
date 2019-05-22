#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "ScoreObserver.h"


class GameObject;
class ScoreObserver;
namespace dae
{
	class ScoreComponent : public BaseComponent
	{
	public:
		explicit ScoreComponent(GameObject* parent,ScoreObserver* scoreObserver);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private: 
		GameObject* m_pParent;
		ScoreObserver* m_ScoreObserver;

		int m_prevScore;
	};
}


