#pragma once
#include <BaseComponent.h>

namespace dae
{
	class UIMainMenu : public BaseComponent
	{
	public:
		explicit UIMainMenu(GameObject* parent);
		virtual ~UIMainMenu() = default;
		UIMainMenu(const UILiveComponent& other) = delete;
		UIMainMenu(UILiveComponent&& other) = delete;
		UIMainMenu& operator=(const UILiveComponent& other) = delete;
		UIMainMenu& operator=(UILiveComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void StartSolo();
		void StartCoOp();
		void StartVS();
		void Quit();

	private:
	};


}
