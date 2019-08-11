#include "pch.h"
#include "SnoBeeAIComponent.h"

dae::SnoBeeAIComponent::SnoBeeAIComponent(GameObject * parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj)
	:BaseComponent(parent)
	,mp_gameGridObj(gameGridObj)
	,m_Speed(Speed)
	,m_WidthAndHeight(WidthAndHeight)
{
}

dae::SnoBeeAIComponent::~SnoBeeAIComponent()
{
}

void dae::SnoBeeAIComponent::Update(const float & deltaTime)
{
	switch ( m_pParent->GetComponent<StateComponent>()->GetState())
	{
		// find out what to do next
	case State::IDLE:
		
		break;

		// stunned and weak
	case State::STRUGGLING:

		break;

		// basic movement
	case State::FACING_LEFT:

		break;
	case State::FACING_RIGHT:

		break;
	case State::FACING_UP:

		break;
	case State::FACING_DOWN:

		break;

		// slowed down movement and destroying the block
	case State::DIGGING_LEFT:

		break;
	case State::DIGGING_RIGHT:

		break;
	case State::DIGGING_UP:

		break;
	case State::DIGGING_DOWN:

		break;

	default:
		break;
	}

}

void dae::SnoBeeAIComponent::Render() const
{
}

dae::Point2f dae::SnoBeeAIComponent::LerpPos(float DT)
{
	T += DT * m_Speed;
	if (T > 1)
	{
		T = 1;
		m_currPos = lerp(m_start, m_destination, T);
		T = 0;
		m_isTraveling = false;
		return m_currPos;
	}
	else
	{
		m_currPos = lerp(m_start, m_destination, T);
		return m_currPos;
	}
}
