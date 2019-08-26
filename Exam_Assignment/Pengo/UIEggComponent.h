#pragma once
#include <BaseComponent.h>
namespace dae
{
	class UIEggComponent : public BaseComponent
	{
	public:
		explicit UIEggComponent(GameObject* parent, GameObserver* GameObserver);
		virtual ~UIEggComponent() = default;
		UIEggComponent(const UIEggComponent& other) = delete;
		UIEggComponent(UIEggComponent&& other) = delete;
		UIEggComponent& operator=(const UIEggComponent& other) = delete;
		UIEggComponent& operator=(UIEggComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		GameObserver* m_GameObserver;

		int m_prevEggs;
	};

}

