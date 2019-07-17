#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "LifeObserver.h"

class GameObject;
class LifeObserver;
namespace dae
{
	class LifeComponent : public BaseComponent
	{
	public:
		explicit LifeComponent(GameObject* parent, LifeObserver* lifeObserver);
		virtual ~LifeComponent() = default;
		LifeComponent(const LifeComponent& other) = delete;
		LifeComponent(LifeComponent&& other) = delete;
		LifeComponent& operator=(const LifeComponent& other) = delete;
		LifeComponent& operator=(LifeComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		LifeObserver* m_lifeObserver;

		int m_prevLife;
	};


}
