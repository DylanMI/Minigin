#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class PookaComponent : public BaseComponent
	{
	public:
		explicit PookaComponent(GameObject* parent);
		virtual ~PookaComponent() = default;
		PookaComponent(const PookaComponent& other) = delete;
		PookaComponent(PookaComponent&& other) = delete;
		PookaComponent& operator=(const PookaComponent& other) = delete;
		PookaComponent& operator=(PookaComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void RandomizeDirection();
		void PutBackAFrame();
		

	private:
		GameObject* m_pParent;
		State m_currentState;
		
		Point2f m_direction;
		Point2f m_previousLocation;

		const float m_GhostTime = 5.0f;
		float m_GhostTimer;
	};


}
