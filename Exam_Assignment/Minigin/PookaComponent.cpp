#include "MiniginPCH.h"
#include "PookaComponent.h"

dae::PookaComponent::PookaComponent(GameObject * parent)
	:m_pParent(parent)
	,m_currentState(State::WANDERING)
	,m_direction({1,0})
	,m_GhostTimer(m_GhostTime)
{
}

void dae::PookaComponent::Update(const float & deltaTime)
{
	switch (m_currentState)
	{
	case State::WANDERING:
		// further ghost timer
		m_GhostTimer -= deltaTime;
		// move 
		m_pParent->Move(m_direction,deltaTime);
		
		
		if (m_direction.x == 0.0f && m_direction.y == 0.0f) ShiftDirection();
		break;

	case State::GHOSTING:
		// move towards player
		// the ghosting will automaticly stop when i goes over something walkable


		break;


	}

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
