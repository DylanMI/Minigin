#pragma once
#include <BaseComponent.h>
namespace dae
{
	class DiamondBlockComponent : public BaseComponent
	{
	public:
		explicit DiamondBlockComponent(GameObject* parent, GameObject * gameGridObj);
		virtual ~DiamondBlockComponent();
		DiamondBlockComponent(const DiamondBlockComponent& other) = delete;
		DiamondBlockComponent(DiamondBlockComponent&& other) = delete;
		DiamondBlockComponent& operator=(const DiamondBlockComponent& other) = delete;
		DiamondBlockComponent& operator=(DiamondBlockComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		GameObject * mp_gameGridObj;


	};
}
