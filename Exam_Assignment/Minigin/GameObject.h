#pragma once
#include <memory>

#include "BaseComponent.h"
#include "FPSComponent.h"
#include "TextRendererComponent.h"

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update(const float& deltaTime) override;
		void Render() const override;
		void SetPosition(Point2f pos);
		Transform GetTransform();

		// adding a component
		void AddComponent(BaseComponent* component);

		// retreiving a component
		template <class Component>
		Component* GetComponent() 
		{
			for (size_t i{}, s = m_pComponents.size(); i < s; i++)
			{
				Component* placeholder = dynamic_cast<Component*>(m_pComponents[i]);
				if (placeholder != nullptr) return placeholder;
			}
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		// legacy var start
		Transform mTransform;
		// legacy var end

		std::vector<BaseComponent*> m_pComponents;

	};
}
