#include "MiniginPCH.h"
#include "Command.h"


dae::Command::~Command()
{
}

void dae::Command::Execute(float /*deltatime*/)
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
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ -1,0 }, deltatime);
}

dae::MoveRightCommandPlayer::MoveRightCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveRightCommandPlayer::~MoveRightCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveRightCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 1,0 }, deltatime);
}

dae::MoveUpCommandPlayer::MoveUpCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveUpCommandPlayer::~MoveUpCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveUpCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 0,1 }, deltatime);
}

dae::MoveDownCommandPlayer::MoveDownCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveDownCommandPlayer::~MoveDownCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveDownCommandPlayer::Execute(float deltatime)
{
	dynamic_cast<PlayerCharacter*>(m_object)->Move(Point2f{ 0,-1 }, deltatime);
}
