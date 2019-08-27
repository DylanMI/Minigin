#include "pch.h"
#include "PlayerSnoMovementComponent.h"

dae::PlayerSnoMovementComponent::PlayerSnoMovementComponent(GameObject * parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj, GameObserver * gameObserver)
	: BaseComponent(parent)
	, m_Speed(Speed)
	, mp_gameGridObj(gameGridObj)
	, m_WidthAndHeight(WidthAndHeight)
	, m_interactTimer(0.0f)
	, m_canInteract(true)
	, mp_GameObserver(gameObserver)
{
	m_prevSpeed = m_Speed;
}

dae::PlayerSnoMovementComponent::~PlayerSnoMovementComponent()
{
}

void dae::PlayerSnoMovementComponent::Update(const float & deltaTime)
{
	m_pParent->SetPosition(m_currPos);

	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::CAUGHTBYBLOCK)
	{
		// if the catcher is a nullptr or something like that, its probably destroyed somehow, die with it
		if (m_CatchedByThis == nullptr)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::DYING);
			Die(400);
		}
		// set the object position to the catchers position
		m_pParent->SetPosition(Point2f{ m_CatchedByThis->GetTransform().GetPosition().x ,m_CatchedByThis->GetTransform().GetPosition().y });
		// if the catcher ever stops sliding, then die
		if (!m_CatchedByThis->GetComponent<IceBlockComponent>()->GetIsSliding())
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::DYING);
			Die(400);
		}
		return;
	}

	// travelling
	if (m_isTraveling && m_pParent->GetComponent<StateComponent>()->GetState() != State::STRUGGLING)
	{
		LerpPos(deltaTime);
	}

	// interact cooldowm
	if (m_canInteract == false)
	{
		m_interactTimer += deltaTime;
		if (m_interactTimer > m_interactCD)
		{
			m_canInteract = true;
			m_interactTimer = 0.0f;
		}
	}

	// sno bee is struggling
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::STRUGGLING)
	{
		m_struggleTimer += deltaTime;
		m_Speed = 0.0f;

		if (m_struggleTimer > m_struggletime)
		{
			m_struggleTimer = 0.0f;
			m_Speed = m_prevSpeed;

		}
	}



	if(m_isTraveling) return;
	int m_prevIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });
	if (m_prevIdx == -1) return;
}

void dae::PlayerSnoMovementComponent::Render() const
{
}

void dae::PlayerSnoMovementComponent::Move(direction direction)
{
	// safeguard
	if (this == nullptr) return;
	if (m_isTraveling) return;
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::STRUGGLING) return;

	// get the current position
	m_prevIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });
	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	// find the new position
	switch (direction)
	{
	case direction::LEFT:
		// change state to looking left
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_LEFT);
		// check if you are at the left border
		if (m_prevIdx == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		if (m_prevIdx % ammPointsW == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = m_prevIdx - 1;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].coordinate;
			m_isTraveling = true;
		}

		// Once you have moved, fix the gameGrid info

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isSnoBee = true;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].object = m_pParent;
		break;
	case direction::RIGHT:
		// change state to looking right
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_RIGHT);
		// you are bottom right
		if (m_prevIdx == mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size() - 1) return;

		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = m_prevIdx + 1;
			return;
		}
		if (m_prevIdx == 0)
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].coordinate;
			m_isTraveling = true;
			return;
		}

		// check if you are at the right border
		if (m_prevIdx % ammPointsW == ammPointsW - 1)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].coordinate;
			m_isTraveling = true;
		}

		// Once you have moved, fix the gameGrid info

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].object = m_pParent;
		break;
	case direction::UP:
		// change state to looking up
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_UP);

		// check if you are at the top border
		if (m_prevIdx - ammPointsW < 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		// check if there is an obstacle there
		else if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = m_prevIdx - ammPointsW;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].coordinate;
			m_isTraveling = true;
		}
		// Once you have moved, fix the gameGrid info

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].object = m_pParent;

		break;
	case direction::DOWN:
		// change state to looking down
		m_pParent->GetComponent<StateComponent>()->SetState(State::FACING_DOWN);

		// check if you are at the bottom border
		if (m_prevIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			return;
		}
		// check if there is an obstacle there
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].isObstacle)
		{
			// do not move
			m_isTraveling = false;
			m_destination = m_currPos;
			// remember the index of it, if you want to push it
			m_lastBumpedIntoIdx = m_prevIdx + ammPointsW;
			return;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].coordinate;
			m_isTraveling = true;
		}
		// Once you have moved, fix the gameGrid info

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].object = m_pParent;
		break;
	}


}

void dae::PlayerSnoMovementComponent::Interact()
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

		// check if the interacted block is the block we tried to push previously
		if (currIdx - ammPointsW == m_lastBumpedIntoIdx)
		{
			// check if its a diamond, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isDiamondBlock) break;

			// check if its an egg, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isEggBlock) break;
			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object = nullptr;


			m_lastBumpedIntoIdx = -1;
		}

		break;
	case State::FACING_DOWN:
		// failsafe
		if (currIdx == -1) return;

		// check if the interacted block is the block we tried to push previously
		if (currIdx + ammPointsW == m_lastBumpedIntoIdx)
		{

			// check if its a diamond, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isDiamondBlock) break;

			// check if its an egg, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isEggBlock) break;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object = nullptr;

			m_lastBumpedIntoIdx = -1;
		}

		break;
	case State::FACING_LEFT:
		// failsafe
		if (currIdx == -1) return;

		// check if the interacted block is the block we tried to push previously
		if (currIdx - 1 == m_lastBumpedIntoIdx)
		{

			// check if its a diamond, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isDiamondBlock) break;
			// check if its an egg, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isEggBlock) break;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object = nullptr;

			m_lastBumpedIntoIdx = -1;
		}
		break;
	case State::FACING_RIGHT:
		// failsafe
		if (currIdx == -1) return;

		// check if the interacted block is the block we tried to push previously
		if (currIdx + 1 == m_lastBumpedIntoIdx)
		{
			// check if its a diamond, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isDiamondBlock) break;

			// check if its an egg, if so then break
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isEggBlock) break;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object = nullptr;


			m_lastBumpedIntoIdx = -1;
		}

		break;


	default:
		break;
	}
}

void dae::PlayerSnoMovementComponent::SetPosition(int idxPos)
{
	m_currPos = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[idxPos].coordinate;
}

void dae::PlayerSnoMovementComponent::SetStartIdx(int idxPos)
{
	m_startIdx = idxPos;
}

void dae::PlayerSnoMovementComponent::GetCatched(GameObject * Catcher)
{
	// failsafe
	if (m_CatchedByThis == Catcher) return;

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	m_isTraveling = false;
	mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx].isSnoBee = false;

	switch (m_pParent->GetComponent<StateComponent>()->GetState())
	{
	case State::FACING_LEFT:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isSnoBee = false;
		break;
	case State::FACING_RIGHT:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isSnoBee = false;
		break;
	case State::FACING_UP:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isSnoBee = false;
		break;
	case State::FACING_DOWN:
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].isSnoBee = false;
		break;
	default:
		break;
	}

	m_CatchedByThis = Catcher;
	m_pParent->GetComponent<StateComponent>()->SetState(State::CAUGHTBYBLOCK);
}

void dae::PlayerSnoMovementComponent::Die(int )
{
	Messenger::GetInstance().Notify(EVENT_ENDGAME, 1);
}

dae::Point2f dae::PlayerSnoMovementComponent::LerpPos(float DT)
{
	T += DT * m_Speed;
	if (T > 1)
	{
		T = 1;
		m_currPos = lerp(m_start, m_destination, T);
		T = 0;
		m_isTraveling = false;
		// fix the grid
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx].object = nullptr;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx].isSnoBee = false;
		return m_currPos;
	}
	else
	{
		m_currPos = lerp(m_start, m_destination, T);
		return m_currPos;
	}
}
