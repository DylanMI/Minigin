#pragma once
#include "BaseComponent.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture2D.h"




// singletons
#include "ResourceManager.h"
#include "Renderer.h"
namespace dae
{
	class TextureComponent final : public BaseComponent
	{
	public:
		explicit TextureComponent(GameObject* parent);
		virtual ~TextureComponent() override;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		void SetIsAnimated(bool IsAnimated);
		bool GetIsAnimated();
		void SetAnimatedSourceRect(SDL_Rect srcrect);

		void SetWidthAndHeight(int width, int height);

	private:
		std::shared_ptr<Texture2D> m_pTexture;
		bool m_isAnimated = false;
		SDL_Rect m_SourceRect;

		int m_width;
		int m_height;
	};
}


