#include "MiniginPCH.h"
#include "Command.h"
#include "CollisionCheckerComponent.h"


dae::Command::~Command()
{
}

void dae::Command::Execute(float /*deltatime*/)
{}

dae::CollisionCommand::~CollisionCommand()
{
}

void dae::CollisionCommand::Execute(float /*deltatime*/, GameObject* /*self*/, GameObject * /*other*/)
{}

dae::MoveLeftCommandPlayer::MoveLeftCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveLeftCommandPlayer::~MoveLeftCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveLeftCommandPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>
}