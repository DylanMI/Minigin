#pragma once
#include "BaseComponent.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "Transform.h"

// singletons
#include "ResourceManager.h"
#include "Renderer.h"
namespace dae
{
	class TextureComponent final : public BaseComponent
	{
	public:
		explicit TextureComponent(GameObject* parent);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void SetTexture(const std::string& filename);
	

	private:
		std::shared_ptr<Texture2D> mTexture;
		GameObject* m_pParent;
	};
}


