#pragma once
#include <memory>

#include "BaseComponent.h"
#include "FPSComponent.h"
#include "TextRendererComponent.h"

#include "Scene.h"
#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

class Scene;
namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		virtual void Update(const float& deltaTime) override;
		virtual void Render() const override;
		virtual void SetPosition(Point2f pos);
		virtual Transform GetTransform();

		// adding a component
		void AddComponent(BaseComponent* component);

		// retreiving a component
		template <class Component>
		Component* GetComponent() 
		{
			for (size_t i{}, s = m_pComponents.size(); i < s; i++)
			{			
				if (dynamic_cast<Component*>(m_pComponents[i]))
				{
					return (Component*)(m_pComponents[i]);
				}
			}
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject() override;
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
