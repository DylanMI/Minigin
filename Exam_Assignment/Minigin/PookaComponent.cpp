#include "MiniginPCH.h"
#include "PookaComponent.h"
dae::PookaComponent::PookaComponent(GameObject * parent)
	:m_pParent(parent)
	,m_currentState(State::WANDERING)
	,m_direction({1,0})
	,m_GhostTimer(m_GhostTime)
{
	m_ToGhostState = new bool(false);
	m_ToWandering = new bool(false);

}

dae::PookaComponent::~PookaComponent()
{
	delete m_ToGhostState;
	delete m_ToWandering;
}

void dae::PookaComponent::Update(const float & deltaTime)
{
	switch (m_currentState)
	{
	case State::WANDERING:
		*m_ToWandering = false;
		SDL_log(m_GhostTimer);
		m_CheckTimer = m_TimeBeforeCheck;

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
