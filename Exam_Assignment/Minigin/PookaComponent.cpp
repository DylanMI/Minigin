#include "MiniginPCH.h"
#include "PookaComponent.h"
dae::PookaComponent::PookaComponent(GameObject * parent)
	:m_pParent(parent)
	,m_currentState(State::WANDERING)
	,m_direction({1,0})
	,m_GhostTimer(m_GhostTime)
	,m_DeflateTimer(m_DeflateTime)
	,m_blowCounter(0)
	
{
	m_ToGhostState = new bool(false);
	m_ToWandering = new bool(false);
	m_IsInflated = new bool(false);
	m_IsNotInflated = new bool(false);
}

dae::PookaComponent::~PookaComponent()
{
	delete m_ToGhostState;
	delete m_ToWandering;
}

void dae::PookaComponent::Update(const float & deltaTime)
{
	*m_IsNotInflated = !*m_IsInflated;

	switch (m_currentState)
	{
	case State::WANDERING:
		*m_ToWandering = false;
		m_CheckTimer = m_TimeBeforeCheck;
		*m_IsInflated = false;

		//  Enable collision checker
		m_pParent->GetComponent<CollisionCheckerComponent>()->SetDisabled(false);

		// further ghost timer
		m_GhostTimer -= deltaTime;
		if (m_GhostTimer < 0)
		{
			*m_ToGhostState = true;
		}

		// move 
		m_pParent->Move(m_direction,deltaTime);	
		if (m_direction.x == 0.0f && m_direction.y == 0.0f) ShiftDirection();


		// change the gameboject state for the animation
		// up
		if (m_direction.x == Point2f{ 0,1 }.x && m_direction.y == Point2f{ 0,1 }.y)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::UP);
		}
		// down
		if (m_direction.x == Point2f{ 0,-1 }.x && m_direction.y == Point2f{ 0,-1 }.y)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::DOWN);
		}
		// left
		if (m_direction.x == Point2f{ -1,0 }.x && m_direction.y == Point2f{ -1,0 }.y)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::LEFT);
		}
		// right
		if (m_direction.x == Point2f{ 1,0 }.x && m_direction.y == Point2f{ 1,0 }.y)
		{
			m_pParent->GetComponent<StateComponent>()->SetState(State::RIGHT);
		}
		break;

	case State::GHOSTING:
		*m_ToGhostState = false;
		m_GhostTimer = m_GhostTime;
		*m_IsInflated = false;

		// disable collision checker
		m_pParent->GetComponent<CollisionCheckerComponent>()->SetDisabled(true);

		// move towards player
		Point2f self = Point2f{m_pParent->GetTransform().GetPosition().x,m_pParent->GetTransform().GetPosition().y};
		Point2f target = Point2f{ m_Target->GetTransform().GetPosition().x,m_Target->GetTransform().GetPosition().y };
		Point2f direction = GetDirectionToTarget(self, target);
		m_pParent->Move(direction, deltaTime);

		m_CheckTimer -= deltaTime;

		// the ghosting will automaticly stop when it goes over something walkable
		if (m_pParent->GetComponent<CollisionCheckerComponent>()->Peek(Point2f{ 0,0 }, Point2f{16,16}) == collisionTag::Nothing && m_CheckTimer < 0)
		{
			*m_ToWandering = true;
		}

		// set the state of the parent to ghosting
		m_pParent->GetComponent<StateComponent>()->SetState(State::GHOSTING);

		break;

	case State::BLOW_1:
	case State::BLOW_2:
	case State::BLOW_3:
	case State::BLOW_4:
		m_DeflateTimer -= deltaTime;

		// handling deflating
		if (m_DeflateTimer < 0)
		{
			m_DeflateTimer = m_DeflateTime;
			m_blowCounter--;
		}

		// telling state machine to go back to wandering
		if (m_blowCounter <= 0)
		{
			*m_IsInflated = false;
		}

		// internally handling the state of the blows
		if (m_blowCounter == 1) m_pParent->GetComponent<StateComponent>()->SetState(State::BLOW_1);
		if (m_blowCounter == 2) m_pParent->GetComponent<StateComponent>()->SetState(State::BLOW_2);
		if (m_blowCounter == 3) m_pParent->GetComponent<StateComponent>()->SetState(State::BLOW_3);
		if (m_blowCounter == 4) m_pParent->GetComponent<StateComponent>()->SetState(State::BLOW_4);

		break;

	}

}

void dae::PookaComponent::Render() const
{
}

void dae::PookaComponent::ShiftDirection()
{

	std::vector<Point2f> possibleDirections{};

	// peek all four sides

	// up
	if (m_pParent->GetComponent<CollisionCheckerComponent>()->Peek(Point2f{ 0,-16 }, Point2f{16,16}) == collisionTag::Nothing)
	{
		possibleDirections.push_back(Point2f{ 0,1 });
	}
	// down
	if (m_pParent->GetComponent<CollisionCheckerComponent>()->Peek(Point2f{ 0,16 }, Point2f{ 16,16 }) == collisionTag::Nothing)
	{
		possibleDirections.push_back(Point2f{ 0,-1 });
	}
	// left
	if (m_pParent->GetComponent<CollisionCheckerComponent>()->Peek(Point2f{ -16,0 }, Point2f{ 16,16 }) == collisionTag::Nothing)
	{
		possibleDirections.push_back(Point2f{ -1,0 });
	}
	// right
	if (m_pParent->GetComponent<CollisionCheckerComponent>()->Peek(Point2f{ 16,0 }, Point2f{ 16,16 }) == collisionTag::Nothing)
	{
		possibleDirections.push_back(Point2f{ 1,0 });
	}

	if (possibleDirections.size() == 0)
	{
		m_direction = Point2f{ 0,0 };
		return;
	}

	int randomnr = rand() % possibleDirections.size();
	m_direction = possibleDirections[randomnr];
}

void dae::PookaComponent::PutBackAFrame(float deltatime)
{
	m_pParent->Move(Point2f{ -m_direction.x, -m_direction.y }, deltatime);
}

void dae::PookaComponent::SetTarget(GameObject * newTarget)
{
	m_Target = newTarget;
}

void dae::PookaComponent::SetState(State newState)
{
	m_currentState = newState;
}

dae::State dae::PookaComponent::GetState()
{
	return m_currentState;
}

bool* dae::PookaComponent::GetToGhostState()
{
	return m_ToGhostState;
}

bool* dae::PookaComponent::GetToWanderingState()
{
	return m_ToWandering;
}

bool * dae::PookaComponent::GetIsInflated()
{
	return m_IsInflated;
}

bool * dae::PookaComponent::GetIsNotInflated()
{
	return m_IsNotInflated;
}

void dae::PookaComponent::SetIsInflated(bool newBool)
{
	*m_IsInflated = newBool;
}

bool * dae::PookaComponent::GetIsDead()
{
	return m_IsDead;
}

void dae::PookaComponent::AddblowCount(int amm)
{
	m_blowCounter += amm;
}
