#include "MiniginPCH.h"
#include "Command.h"


void dae::Command::Execute(float /*deltatime*/)
{}

dae::MoveLeftCommandPlayer::MoveLeftCommandPlayer(GameObject * object)
	:m_object(object)
{}

void dae::MoveLeftCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ -1,0 }, deltatime);
}

dae::MoveRightCommandPlayer::MoveRightCommandPlayer(GameObject * object)
	:m_object(object)
{}

void dae::MoveRightCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 1,0 }, deltatime);
}

dae::MoveUpCommandPlayer::MoveUpCommandPlayer(GameObject * object)
	:m_object(object)
{}

void dae::MoveUpCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 0,1 }, deltatime);
}

dae::MoveDownCommandPlayer::MoveDownCommandPlayer(GameObject * object)
	:m_object(object)
{}

void dae::MoveDownCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 0,-1 }, deltatime);
}
