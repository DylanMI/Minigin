#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class GameFieldGridComponent : public BaseComponent
	{
	public:
		explicit GameFieldGridComponent(GameObject* parent);
		virtual ~GameFieldGridComponent();
		GameFieldGridComponent(const GameFieldGridComponent& other) = delete;
		GameFieldGridComponent(GameFieldGridComponent&& other) = delete;
		GameFieldGridComponent& operator=(const GameFieldGridComponent& other) = delete;
		GameFieldGridComponent& operator=(GameFieldGridComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	};

}
