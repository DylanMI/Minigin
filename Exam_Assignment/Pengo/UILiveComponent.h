#pragma once
#include <BaseComponent.h>

namespace dae
{
	class UILiveComponent : public BaseComponent
	{
	public:
		explicit UILiveComponent(GameObject* parent, GameObserver* GameObserver);
		virtual ~UILiveComponent() = default;
		UILiveComponent(const UILiveComponent& other) = delete;
		UILiveComponent(UILiveComponent&& other) = delete;
		UILiveComponent& operator=(const UILiveComponent& other) = delete;
		UILiveComponent& operator=(UILiveComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		GameObserver* m_GameObserver;

		int m_prevLives;
	};
}



