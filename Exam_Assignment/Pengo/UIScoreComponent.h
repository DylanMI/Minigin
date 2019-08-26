#pragma once
#include <BaseComponent.h>
namespace dae
{
	class UIScoreComponent : public BaseComponent
	{
	public:
		explicit UIScoreComponent(GameObject* parent, GameObserver* GameObserver);
		virtual ~UIScoreComponent() = default;
		UIScoreComponent(const UIScoreComponent& other) = delete;
		UIScoreComponent(UIScoreComponent&& other) = delete;
		UIScoreComponent& operator=(const UIScoreComponent& other) = delete;
		UIScoreComponent& operator=(UIScoreComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		GameObserver* m_GameObserver;

		int m_prevScore;
	};
}

