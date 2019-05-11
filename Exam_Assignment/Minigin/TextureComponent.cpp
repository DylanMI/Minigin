#include "MiniginPCH.h"
#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject * parent)
	: m_pParent (parent)
{
}

void dae::TextureComponent::Update(const float & /*deltaTime*/)
{
	
}

void dae::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*mTexture, m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y);
}

void dae::TextureComponent::SetTexture(const std::string & filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
