#include "MiniginPCH.h"
#include "PlayerCharacter.h"

dae::State dae::PlayerCharacter::GetState()
{
	return m_CurrentState;
}

void dae::PlayerCharacter::SetState(State newState)
{
	m_CurrentState = newState;
}

float dae::PlayerCharacter::GetSpeed()
{
	return m_speed;
}

void dae::PlayerCharacter::SetSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

void dae::PlayerCharacter::SetBoundaries(Rectf boundry)
{
	m_mapBoundry = boundry;
}

void dae::PlayerCharacter::SetPosition(Point2f pos)
{
	mTransform.SetPosition(pos.x, pos.y, 0.0f);
}

dae::Transform dae::PlayerCharacter::GetTransform()
{
	return mTransform;
}

void dae::PlayerCharacter::Move(Point2f direction, float deltaTime)
{
	// make it 4 axis instead of ... ehm, more? (preventing diagonal)
	Point2f correctedDirection{};
	if (direction.x == 1)
	{
		correctedDirection.x = 1;
		correctedDirection.y = 0;
	}
	else if (direction.x == -1)
	{
		correctedDirection.x = -1;
		correctedDirection.y = 0;
	}
	else if (direction.y == 1)
	{
		correctedDirection.x = 0;
		correctedDirection.y = 1;
	}
	else if (direction.y == -1)
	{
		correctedDirection.x = 0;
		correctedDirection.y = -1;
	}

	// right
	if (correctedDirection.x == 1) m_CurrentState = State::RIGHT;
	// left
	if (correctedDirection.x == -1) m_CurrentState = State::LEFT;
	// up
	if (correctedDirection.y == 1) m_CurrentState = State::UP;
	//down
	if (correctedDirection.y == -1) m_CurrentState = State::DOWN;
	Point2f newpos;
	// the moving
	newpos = { mTransform.GetPosition().x , mTransform.GetPosition().y };
	newpos.x += (correctedDirection.x * m_speed) * deltaTime;
	newpos.y += (-correctedDirection.y * m_speed) * deltaTime;
	SDL_log(correctedDirection.x);
	SDL_log(correctedDirection.y);
	// the collision checking


	// pushing the change
	SetPosition(newpos);
}

dae::PlayerCharacter::~PlayerCharacter()
{
}
