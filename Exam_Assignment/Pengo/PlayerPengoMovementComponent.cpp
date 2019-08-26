#include "pch.h"
#include "PlayerPengoMovementComponent.h"
#include <cmath>
dae::PlayerPengoMovementComponent::PlayerPengoMovementComponent(GameObject * parent, Point2f WidthAndHeight, float TimeToTravel, GameObject * gameGridObj)
	: BaseComponent(parent)
	, m_Speed(TimeToTravel)
	, mp_gameGridObj(gameGridObj)
	, m_WidthAndHeight(WidthAndHeight)
	,m_interactTimer(0.0f)
	,m_canInteract(true)
{
}

dae::PlayerPengoMovementComponent::~PlayerPengoMovementComponent()
{
}

void dae::PlayerPengoMovementComponent::Update(const float & deltaTime)
{
	m_pParent->SetPosition(m_currPos);

	if (m_canInteract == false)
	{
		m_interactTimer += deltaTime;
		if (m_interactTimer > m_interactCD)
		{
			m_canInteract = true;
			m_interactTimer = 0.0f;
		}
	}

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
	int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y}); 
	
	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();
	
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
			return;
		}
		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = currIdx - 1;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].coordinate;
			m_isTraveling = true;
		}
		break;
	case direction::RIGHT:
		// change state to looking right
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_RIGHT);
		// you are bottom right
		if (currIdx == mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size() - 1) return;

		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = currIdx + 1;
			return;
		}
		if (currIdx == 0)
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].coordinate;
			m_isTraveling = true;
			return;
		}

		// check if you are at the right border
		if (currIdx % ammPointsW == ammPointsW - 1)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].coordinate;
			m_isTraveling = true;
		}

		break;
	case direction::UP:
		// change state to looking up
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_UP);
		
		// check if you are at the top border
		if (currIdx - ammPointsW < 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
		}
		// check if there is an obstacle there
		else if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = currIdx - ammPointsW;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].coordinate;
			m_isTraveling = true;
		}

		break;
	case direction::DOWN:
		// change state to looking down
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_DOWN);
		
		// check if you are at the bottom border
		if (currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = currIdx + ammPointsW;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].coordinate;
			m_isTraveling = true;
		}

		break;
	}


}

void dae::PlayerPengoMovementComponent::Interact()
{
	if (m_canInteract == false) return;
	// get the current position
	int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	// get current state
	State currentState = m_pParent->GetComponent<StateComponent>()->GetState();

	switch (currentState)
	{
	case State::FACING_UP:
		// failsafe
		if (currIdx == -1) return;
		// check if you are at the wall
		if (currIdx - ammPointsW < 0)
		{
			StunBees(direction::UP, ammPointsW, ammPointsH);
		}

		// check if the interacted block is the block we tried to push previously
		if (currIdx - ammPointsW == m_lastBumpedIntoIdx)
		{
			// try to push it
			if (!mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_lastBumpedIntoIdx].object->GetComponent<IceBlockComponent>()->StartGliding(direction::UP))
			{
				// check if its a diamond, if so then break
				if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isDiamondBlock) break;
				// break it
				// tell the block to break
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
				// tell the grid to forget about that block
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isObstacle = false;
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object = nullptr;

			}

			m_lastBumpedIntoIdx = -1;
		}

		break;
	case State::FACING_DOWN:
		// failsafe
		if (currIdx == -1) return;
		// check if you are at a wall
		if (currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
		{
			StunBees(direction::DOWN, ammPointsW, ammPointsH);
		}
		
		// check if the interacted block is the block we tried to push previously
		if (currIdx + ammPointsW == m_lastBumpedIntoIdx)
		{
			// try to push it
			if (! mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_lastBumpedIntoIdx].object->GetComponent<IceBlockComponent>()->StartGliding(direction::DOWN))
			{
				// check if its a diamond, if so then break
				if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isDiamondBlock) break;
				// break it
				// tell the block to break
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
				// tell the grid to forget about that block
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isObstacle = false;
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object = nullptr;

			}
			m_lastBumpedIntoIdx = -1;
		}

		break;
	case State::FACING_LEFT:
		// failsafe
		if (currIdx == -1) return;
		// check if you are at a wall
		if (currIdx == 0 || currIdx % ammPointsW == 0)
		{
			StunBees(direction::LEFT, ammPointsW, ammPointsH);
			return;
		}
		// check if the interacted block is the block we tried to push previously
		if (currIdx - 1 == m_lastBumpedIntoIdx)
		{
			// try to push it
			if (! mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_lastBumpedIntoIdx].object->GetComponent<IceBlockComponent>()->StartGliding(direction::LEFT))
			{
				// check if its a diamond, if so then break
				if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isDiamondBlock) break;
				// break it
				// tell the block to break
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
				// tell the grid to forget about that block
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isObstacle = false;
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object = nullptr;

			}
			m_lastBumpedIntoIdx = -1;
		}
		
		break;
	case State::FACING_RIGHT:
		// failsafe
		if (currIdx == -1) return;
		// check if you are at a wall
		if (currIdx % ammPointsW == ammPointsW - 1)
		{
			StunBees(direction::RIGHT, ammPointsW, ammPointsH);
		}
		// check if the interacted block is the block we tried to push previously
		if (currIdx + 1 == m_lastBumpedIntoIdx)
		{
			// try to push it
			if (!mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_lastBumpedIntoIdx].object->GetComponent<IceBlockComponent>()->StartGliding(direction::RIGHT))
			{
				// check if its a diamond, if so then break
				if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isDiamondBlock) break;
				// break it
				// tell the block to break
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
				// tell the grid to forget about that block
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isObstacle = false;
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object = nullptr;

			}
			m_lastBumpedIntoIdx = -1;
		}

		break;


	default:
		break;
	}


	m_canInteract = false;
}

void dae::PlayerPengoMovementComponent::SetPosition(int idxPos)
{
	m_currPos = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[idxPos].coordinate;
}

dae::Point2f dae::PlayerPengoMovementComponent::LerpPos(float DT)
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

void dae::PlayerPengoMovementComponent::StunBees(direction dir, int ammPointsW, int ammPointsH)
{
	switch (dir)
	{
	case dae::LEFT:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->ActivateWall(direction::LEFT);
		// tell the left row to stun sno bees
		for (int i{}; i < ammPointsW; i++)
		{
			int offset = i * ammPointsW - 1;
			if (i == 0) offset = 0;

			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[offset].isSnoBee)
			{
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[offset].object->GetComponent<StateComponent>()->SetState(State::STRUGGLING);
			}
		}
		break;
	case dae::RIGHT:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->ActivateWall(direction::RIGHT);

		break;
	case dae::UP:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->ActivateWall(direction::UP);
		// tell the top row to stun sno bees
		for (int i{}; i < ammPointsW; i++)
		{
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[i].isSnoBee)
			{
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[i].object->GetComponent<StateComponent>()->SetState(State::STRUGGLING);
			}
		}
		break;
	case dae::DOWN:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->ActivateWall(direction::DOWN);
		// tell the bottom row to stun sno bees
		for (int i{}; i < ammPointsW; i++)
		{
			int offset = (ammPointsW * ammPointsH) - ammPointsW - 1;
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[offset + i].isSnoBee)
			{
				mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[offset + i].object->GetComponent<StateComponent>()->SetState(State::STRUGGLING);
			}
		}
		break;
	case dae::NONE:
		break;
	default:
		break;
	}
}
