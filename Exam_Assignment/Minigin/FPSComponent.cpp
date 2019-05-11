#include "MiniginPCH.h"
#include "FPSComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

dae::FPSComponent::FPSComponent(GameObject*parent)
	: m_pParent(parent)
{
}

void dae::FPSComponent::Update(const float& deltaTime)
{
	// calculate the fps
	m_FPS = 1 / deltaTime;

	// update the fps to the text renderer from the parent if it has one
	TextRendererComponent* placeholder = m_pParent->GetComponent<TextRendererComponent>();
	placeholder->ChangeText("FPS: " + std::to_string(int(m_FPS)));
}

void dae::FPSComponent::Render() const
{
}

void dae::FPSComponent::SetPosition(dae::Point2f newPosition)
{
	m_position = newPosition;
}

dae::Point2f dae::FPSComponent::GetPosition()
{
	return m_position;
}

float dae::FPSComponent::GetFPS()
{
	return m_FPS;
}




