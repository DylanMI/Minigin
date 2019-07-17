#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextRendererComponent final : public dae::BaseComponent
	{
	public:

		TextRendererComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* parent);
		virtual ~TextRendererComponent() override;

		TextRendererComponent(const TextRendererComponent& other) = delete;
		TextRendererComponent(TextRendererComponent&& other) = delete;
		TextRendererComponent& operator=(const TextRendererComponent& other) = delete;
		TextRendererComponent& operator=(TextRendererComponent&& other) = delete;
		
		void Update(const float& deltaTime) override;
		void Render() const override;
		void ChangeText(std::string newString);
		void SetPosition(const float x, const float y);

	private:
		std::string m_Text;
		dae::Transform m_Transform;
		std::shared_ptr<dae::Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};

}


