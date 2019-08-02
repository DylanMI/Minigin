#include "pch.h"
#include "GameCommand.h"

dae::GameCommand::~GameCommand()
{
}

void dae::GameCommand::Execute(float deltatime)
{
}

dae::GameCollisionCommand::~GameCollisionCommand()
{
}

void dae::GameCollisionCommand::Execute(float deltatime, GameObject * self, GameObject * other)
{
}

dae::MoveLeftCommandPlayer::MoveLeftCommandPlayer(GameObject * object)
	: m_object(object)
{}

dae::MoveLeftCommandPlayer::~MoveLeftCommandPlayer()
{
	//delete m_object;
}

void dae::MoveLeftCommandPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>()->Move(direction::LEFT);
}

dae::MoveRightCommandPlayer::MoveRightCommandPlayer(GameObject * object)
	: m_object(object)
{}

dae::MoveRightCommandPlayer::~MoveRightCommandPlayer()
{
	//delete m_object;
}

void dae::MoveRightCommandPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>()->Move(direction::RIGHT);
}

dae::MoveUpCommandPlayer::MoveUpCommandPlayer(GameObject * object)
	: m_object(object)
{}

dae::MoveUpCommandPlayer::~MoveUpCommandPlayer()
{
	//delete m_object;
}

void dae::MoveUpCommandPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>()->Move(direction::UP);
}

dae::MoveDownCommandPlayer::MoveDownCommandPlayer(GameObject * object)
	: m_object(object)
{}

dae::MoveDownCommandPlayer::~MoveDownCommandPlayer()
{
	//delete m_object;
}

void dae::MoveDownCommandPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>()->Move(direction::DOWN);
}
