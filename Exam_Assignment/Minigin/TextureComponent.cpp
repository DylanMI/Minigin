#include "MiniginPCH.h"
#include "TextureComponent.h"

dae::TextureComponent::TextureComponent(GameObject * parent)
	: m_pParent (parent)
{
}

dae::TextureComponent::~TextureComponent()
{
	m_pParent = nullptr;
	delete m_pParent;
}

void dae::TextureComponent::Update(const float & /*deltaTime*/)
{
	
}

void dae::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y);
}

void dae::TextureComponent::SetTexture(const std::string & filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	
}
