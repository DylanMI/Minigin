#include "MiniginPCH.h"
#include "TextRendererComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextRendererComponent::TextRendererComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* parent)
	: m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
	, m_pParent(parent)
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto SDLsurf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (SDLsurf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), SDLsurf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(SDLsurf);
	m_Texture = std::make_shared<Texture2D>(texture);
}
dae::TextRendererComponent::~TextRendererComponent()
{
	m_pParent = nullptr;
	delete m_pParent;
}


void dae::TextRendererComponent::Update(const float& )
{

}

void dae::TextRendererComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);	
	}
}

void dae::TextRendererComponent::ChangeText(std::string newString)
{
	m_Text = newString;

	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto SDLsurf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (SDLsurf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), SDLsurf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(SDLsurf);
	m_Texture = std::make_shared<Texture2D>(texture);

}

void dae::TextRendererComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

