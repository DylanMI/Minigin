#include "pch.h"
#include "WallComponent.h"

dae::WallComponent::WallComponent(GameObject * parent)
	:BaseComponent(parent)
	, m_redTime(2.0f)
	, m_redTimer(0.0f)
	, m_isRed(false)
{


}

dae::WallComponent::~WallComponent()
{

}

void dae::WallComponent::Update(const float & deltaTime)
{
	if (m_isRed)
	{
		m_redTimer += deltaTime;
		if (m_redTimer > m_redTime)
		{
			m_isRed = false;
			// set the texture back
			m_pParent->GetComponent<TextureComponent>()->SetTexture("WallBlue.png");
			m_redTimer = 0.0f;
		}
	}
}

void dae::WallComponent::Render() const
{

}

void dae::WallComponent::Activate()
{
	m_isRed = true;
	m_pParent->GetComponent<TextureComponent>()->SetTexture("WallRed.png");
}
