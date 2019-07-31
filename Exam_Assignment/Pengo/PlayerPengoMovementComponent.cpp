#include "pch.h"
#include "PlayerPengoMovementComponent.h"
#include <cmath>
dae::PlayerPengoMovementComponent::PlayerPengoMovementComponent(GameObject * parent, float TimeToTravel)
	: BaseComponent(parent)
	, m_Speed(TimeToTravel)
{
}

dae::PlayerPengoMovementComponent::~PlayerPengoMovementComponent()
{
}

void dae::PlayerPengoMovementComponent::Update(const float & deltaTime)
{
	if (m_isTraveling)
	{
		LerpPos(deltaTime);
	}
}

void dae::PlayerPengoMovementComponent::Render() const
{
}

dae::Point2f dae::PlayerPengoMovementComponent::LerpPos(float DT)
{
	T += DT;
	T -= m_Speed;
	if (T > 1)
	{
		T = 1;
		m_currPos = lerp(m_start, m_destination, T);
		T = 0;
		m_isTraveling = false;
		return;
	}
	else
	{
		m_currPos = lerp(m_start, m_destination, T);
	}
}
