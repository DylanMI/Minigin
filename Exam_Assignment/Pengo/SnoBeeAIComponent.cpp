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
	// get the current position
	int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	State randState = State::IDLE;

	if (m_isTraveling && m_pParent->GetComponent<StateComponent>()->GetState() != State::CAUGHTBYBLOCK)
	{
		LerpPos(deltaTime);
	}

	m_pParent->SetPosition(m_currPos);

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

		// stunned and weak
	case State::STRUGGLING:

		break;

		// basic movement
	case State::FACING_LEFT:
		if (m_isTraveling) return;
		// check if you are at the left border
		if (currIdx == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}
		if (currIdx % ammPointsW == 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}

		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isObstacle)
		{
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object = nullptr;

			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_LEFT);
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].coordinate;
			m_isTraveling = true;
		}
		
		// Once you have moved, fix the gameGrid info
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].isSnoBee = false;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].object = nullptr;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].object = m_pParent;


		break;

	case State::FACING_RIGHT:
		if (m_isTraveling) return;
		// check if you are at the right border
		if (currIdx % ammPointsW == ammPointsW - 1)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}


		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isObstacle)
		{
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object = nullptr;

			// set the animation state		
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_RIGHT);
		}
		else if (currIdx == 0)
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].coordinate;
			m_isTraveling = true;
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].coordinate;
			m_isTraveling = true;
		}

		// Once you have moved, fix the gameGrid info
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].isSnoBee = false;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].object = nullptr;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].object = m_pParent;
		break;


	case State::FACING_UP:
		if (m_isTraveling) return;
		// check if you are at the top border
		if (currIdx - ammPointsW < 0)
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}


		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isObstacle)
		{
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object = nullptr;

			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_UP);
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].coordinate;
			m_isTraveling = true;
		}

		// Once you have moved, fix the gameGrid info
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].isSnoBee = false;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].object = nullptr;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].object = m_pParent;

		break;

	case State::FACING_DOWN:
		if (m_isTraveling) return;
		// check if you are at the bottom border
		if (currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
		{
			m_isTraveling = false;
			m_destination = m_currPos;
			m_pParent->GetComponent<StateComponent>()->SetState(State::IDLE);
			return;
		}

		// check if there is an obstacle there, then set the state accordingly
		if (mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isObstacle)
		{
			// move but set the Diggingbool
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].coordinate;
			m_IsDigging = true;
			m_isTraveling = true;

			// tell the block to break
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object->GetComponent<IceBlockComponent>()->StartBreaking(m_Speed / 2.0f);
			
			// tell the grid to forget about that block
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isObstacle = false;
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object = nullptr;
			
			// set the animation state
			m_pParent->GetComponent<StateComponent>()->SetState(State::DIGGING_DOWN);
		}
		// else set destination there
		else
		{
			m_start = m_currPos;
			m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].coordinate;
			m_isTraveling = true;
		}

		// Once you have moved, fix the gameGrid info
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].isSnoBee = false;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isSnoBee = true;

		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx].object = nullptr;
		mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].object = m_pParent;

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
		return m_currPos;
	}
	else
	{
		m_currPos = lerp(m_start, m_destination, T);
		return m_currPos;
	}
}