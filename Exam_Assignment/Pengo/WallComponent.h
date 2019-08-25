#pragma once
#include <BaseComponent.h>
namespace dae
{
	class WallComponent : public BaseComponent
	{
	public:
		explicit WallComponent(GameObject* parent);
		virtual ~WallComponent();
		WallComponent(const GameFieldGridComponent& other) = delete;
		WallComponent(WallComponent&& other) = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void Activate();
	private:

		float m_redTime;
		float m_redTimer;

		bool m_isRed;



	};

}

