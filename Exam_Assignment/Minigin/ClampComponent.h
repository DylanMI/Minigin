#pragma once
#include "BaseComponent.h"
#include "GameObject.h"


class GameObject;
namespace dae
{
	class ClampComponent : public BaseComponent
	{
	public:
		explicit ClampComponent(GameObject* parent);
		virtual ~ClampComponent() = default;
		ClampComponent(const ClampComponent& other) = delete;
		ClampComponent(ClampComponent&& other) = delete;
		ClampComponent& operator=(const ClampComponent& other) = delete;
		ClampComponent& operator=(ClampComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void SetClampRect(Rectf newRect);
		bool CheckClamp(Point2f position, Point2f WidthAndHeight);


	private:
		GameObject* m_pParent;
		Rectf m_ClampRect;

	};

}

