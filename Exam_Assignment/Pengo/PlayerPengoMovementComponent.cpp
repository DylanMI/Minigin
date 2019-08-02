#include "pch.h"
#include "PlayerPengoMovementComponent.h"
#include <cmath>
dae::PlayerPengoMovementComponent::PlayerPengoMovementComponent(GameObject * parent, Point2f WidthAndHeight, float TimeToTravel, GameObject * gameGridObj)
	: BaseComponent(parent)
	, m_Speed(TimeToTravel)
	, m_gameGridObj(gameGridObj)
	, m_WidthAndHeight(WidthAndHeight)
{
}

dae::PlayerPengoMovementComponent::~PlayerPengoMovementComponent()
{
}

void dae::PlayerPengoMovementComponent::Update(const float & deltaTime)
{
	m_pParent->SetPosition(m_currPos);

	if (m_isTraveling)
	{
		LerpPos(deltaTime);
	}
}

void dae::PlayerPengoMovementComponent::Render() const
{
}

void dae::PlayerPengoMovementComponent::Move(direction direction)
{
	if (m_isTraveling) return;

	// get the current position
	int currIdx = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y}); 
	
	int ammPointsW = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();
	
	// find the new position
	switch (direction)
	{
	case direction::LEFT:
		// change state to looking left
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_LEFT);
		// check if you are at the left border
		if (currIdx == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		if (currIdx % ammPointsW == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[currIdx - 1].coordinate;
			m_isTraveling = true;
		}
		break;
	case direction::RIGHT:
		// change state to looking left
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_RIGHT);
		if (currIdx == 0)
		{
			m_start = m_currPos;
			m_destination = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[currIdx + 1].coordinate;
			m_isTraveling = true;
			return;
		}

		// check if you are at the right border
		if (ammPointsW % currIdx == ammPointsW - 1)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[currIdx + 1].coordinate;
			m_isTraveling = true;
		}

		break;
	case direction::UP:
		// change state to looking left
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_UP);


		break;
	case direction::DOWN:
		// change state to looking left
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_DOWN);


		break;
	}


}

void dae::PlayerPengoMovementComponent::SetPosition(int idxPos)
{
	m_currPos = m_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[idxPos].coordinate;
}

dae::Point2f dae::PlayerPengoMovementComponent::LerpPos(float DT)
{
	T += DT;
	//T *= m_Speed;
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
