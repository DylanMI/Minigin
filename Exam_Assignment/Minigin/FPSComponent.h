#pragma once
#include "SceneObject.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextRendererComponent.h"
#include "BaseComponent.h"
#include "Structs.h"

class Font;
class BaseComponent;
class GameObject;
namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		explicit FPSComponent(GameObject* parent);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;	
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetPosition(dae::Point2f newPosition);
		dae::Point2f GetPosition();
		float GetFPS();
	
	private:
		dae::Point2f m_position;
		float m_FPS;

	};
}

