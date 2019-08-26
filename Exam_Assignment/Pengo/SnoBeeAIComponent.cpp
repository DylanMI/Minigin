#include "pch.h"
#include "SnoBeeAIComponent.h"

dae::SnoBeeAIComponent::SnoBeeAIComponent(GameObject * parent, Point2f WidthAndHeight, float Speed, GameObject * gameGridObj)
	:BaseComponent(parent)
	,mp_gameGridObj(gameGridObj)
	,m_Speed(Speed)
	,m_WidthAndHeight(WidthAndHeight)
{
	m_prevSpeed = m_Speed;
}

dae::SnoBeeAIComponent::~SnoBeeAIComponent()
{
	
}

void dae::SnoBeeAIComponent::Update(const float & deltaTime)
{

	State randState = State::IDLE;
	if (m_isTraveling && m_pParent->GetComponent<StateComponent>()->GetState() != State::CAUGHTBYBLOCK)
	{
		LerpPos(deltaTime);
	}

	m_pParent->SetPosition(m_currPos);

	// sno bee is struggling
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::STRUGGLING)
	{
		m_struggleTimer += deltaTime;
		m_Speed = 0.0f;

		if (m_struggleTimer > m_struggletime)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			m_struggleTimer = 0.0f;
			m_Speed = m_prevSpeed;

		}
	}

	// get the current position
	if (m_isTraveling) return;

	m_prevIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	switch ( m_pParent->GetComponent<StateComponent>()->GetState())
	{
		// find out what to do next
	case State::IDLE:
		// reset digging bool
		m_IsDigging = false;
		// randomize between the four directions
		randState =  State(rand() % 4);
		// then change the actual state
		m_pParent->GetComponent<StateComponent>()->SetState(randState);

		break;

		// basic movement
	case State::FACING_LEFT:
		if (m_isTraveling) return;
		// check if you are at the left border
		if (m_prevIdx == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}
		if (m_prevIdx % ammPointsW == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}

		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isObstacle)
		{
			// check if the block is moving
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].object->GetComponent<IceBlockComponent>()->GetIsSliding()) return;

			// check if the block is a diamond
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isDiamondBlock) return;

			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - 1].object = nullptr;

			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_LEFT);
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

	case State::FACING_RIGHT:
		if (m_isTraveling) return;
		// check if you are at the right border
		if (m_prevIdx % ammPointsW == ammPointsW - 1)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}


		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isObstacle)
		{
			// check if the block is moving
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].object->GetComponent<IceBlockComponent>()->GetIsSliding()) return;
			// check if the block is a diamond
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isDiamondBlock) return;
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].object = nullptr;

			// set the animation state		
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_RIGHT);
		}
		else if (m_prevIdx == 0)
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + 1].coordinate;
			m_isTraveling = true;
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


	case State::FACING_UP:
		if (m_isTraveling) return;
		// check if you are at the top border
		if (m_prevIdx - ammPointsW < 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}


		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isObstacle)
		{
			// check if the block is moving
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].object->GetComponent<IceBlockComponent>()->GetIsSliding()) return;
			// check if the block is a diamond
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isDiamondBlock) return;
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx - ammPointsW].object = nullptr;

			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_UP);
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

	case State::FACING_DOWN:
		if (m_isTraveling) return;
		// check if you are at the bottom border
		if (m_prevIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}

		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].isObstacle)
		{
			// check if the block is moving
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].object->GetComponent<IceBlockComponent>()->GetIsSliding()) return;
			// check if the block is a diamond
			if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx +ammPointsW].isDiamondBlock) return;
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx + ammPointsW].object = nullptr;
			
			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_DOWN);
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

	case State::CAUGHTBYBLOCK:
		// set the object position to the catchers position
		m_pParent->SetPosition(Point2f{ m_CatchedByThis->GetTransform().GetPosition().x ,m_CatchedByThis->GetTransform().GetPosition().y });
		// if the catcher ever stops sliding, then die
		if (!m_CatchedByThis->GetComponent<IceBlockComponent>()->GetIsSliding())
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::DYING);		
			Die(400);
		}

		break;
		 
	default:
		break;
	}
}

void dae::SnoBeeAIComponent::Render() const
{
}

void dae::SnoBeeAIComponent::SetPosition(int idxPos)
{
	m_currPos = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[idxPos].coordinate;
}

void dae::SnoBeeAIComponent::GetCatched(GameObject * Catcher)
{
	// failsafe
	if (m_CatchedByThis == Catcher) return;
	

	m_isTraveling = false;
	mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[m_prevIdx].isSnoBee = false;

	m_CatchedByThis = Catcher;
	m_pParent->GetComponent<StateComponent>()->SetState(State::CAUGHTBYBLOCK);
}

void dae::SnoBeeAIComponent::Die(int ScoreForDeath)
{
	// load font 
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	// make text object with score value
	auto mp_ScoreText = new dae::GameObject();

	// -- give the text component
	mp_ScoreText->AddComponent(new TextRendererComponent(std::to_string(ScoreForDeath), font, mp_ScoreText));

	// -- give the self destruct component
	mp_ScoreText->AddComponent(new DeleteSelfComponent(mp_ScoreText, mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getSceneRef()));
	// and tell it delete itself after a while
	mp_ScoreText->GetComponent<DeleteSelfComponent>()->StartSelfDestruct(2.0f);

	// add the object
	mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getSceneRef().Add(mp_ScoreText);

	// set the location
	mp_ScoreText->GetComponent<TextRendererComponent>()->SetPosition(m_pParent->GetTransform().GetPosition().x, m_pParent->GetTransform().GetPosition().y);

	// send the event
	Messenger::GetInstance().Notify(EVENT_ENEMYDIED, ScoreForDeath);

	// remove your data from the gamegrid
	mp_gameGridObj->GetComponent<GameFieldGridComponent>()->RemoveData(m_pParent);

	// and finally, kill yourself ... finally .... an end to eternal suffering
	m_pParent->AddComponent(new DeleteSelfComponent(m_pParent, mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getSceneRef()));
	m_pParent->GetComponent<DeleteSelfComponent>()->KillNow();
}

dae::Point2f dae::SnoBeeAIComponent::LerpPos(float DT)
{
	if (m_IsDigging) T += DT * (m_Speed / 2.0f);
	else T += DT * m_Speed;
	if (T > 1)
	{
		T = 1;
		m_currPos = lerp(m_start, m_destination, T);
		T = 0;
		m_isTraveling = false;
		m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
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
