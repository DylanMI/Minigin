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
	if (m_pTexture == nullptr) return;
	if (m_isAnimated)
	{
		
		SDL_Rect dst;
		dst.x = static_cast<int>(m_pParent->GetTransform().GetPosition().x);
		dst.y = static_cast<int>(m_pParent->GetTransform().GetPosition().y);
		dst.w = 32;
		dst.h = 32;
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_SourceRect, dst);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y,m_width,m_height);
	}

}

void dae::TextureComponent::SetTexture(const std::string & filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_pTexture = texture;
}

void dae::TextureComponent::SetIsAnimated(bool IsAnimated)
{
	m_isAnimated = IsAnimated;
}

void dae::TextureComponent::SetAnimatedSourceRect(SDL_Rect srcrect)
{
	m_SourceRect = srcrect;
}

void dae::TextureComponent::SetWidthAndHeight(int width, int height)
{
	m_width = width;
	m_height = height;
}
