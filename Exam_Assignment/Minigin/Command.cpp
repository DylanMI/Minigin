#include "MiniginPCH.h"
#include "Command.h"


dae::Command::~Command()
{
}

void dae::Command::Execute(float /*deltatime*/)
{}

dae::CollisionCommand::~CollisionCommand()
{
}

void dae::CollisionCommand::Execute(float /*deltatime*/, GameObject * /*other*/)
{}



#pragma region movementcommands
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
#pragma endregion

#pragma region RockCommands

dae::FallCommandRock::FallCommandRock(GameObject * object)
	:m_object(object)
{}

dae::FallCommandRock::~FallCommandRock()
{
	m_object = nullptr;
}

// executed when the collision doesn't collide with anyting
void dae::FallCommandRock::Execute(float , GameObject* /*other*/)
{
	// check if the rock is already falling, if not make it falling
	if (!m_object->GetComponent<RockComponent>()->GetIsFalling())
	{
		m_object->GetComponent<RockComponent>()->SetIsFalling(true);

		// also change the body to fit the rock itself (AKA: no offset)


	}
}

dae::BreakCommandRock::BreakCommandRock(GameObject * object)
	:m_object(object)
{}

dae::BreakCommandRock::~BreakCommandRock()
{
	m_object = nullptr;
}

// exectuted after the collision detects terrain and is falling
void dae::BreakCommandRock::Execute(float , GameObject* /*other*/)
{
	// check if the rock is falling, if yes then set it to breaking
	if (m_object->GetComponent<RockComponent>()->GetIsFalling())
	{
		m_object->GetComponent<RockComponent>()->SetIsBreaking(true);
	}
}

dae::TakeEnemyCommandRock::TakeEnemyCommandRock(GameObject * object)
	:m_object(object)
{}

dae::TakeEnemyCommandRock::~TakeEnemyCommandRock()
{
	m_object = nullptr;
}

// exectuted when the collision detects an enemy and is falling
void dae::TakeEnemyCommandRock::Execute(float , GameObject* )
{
	// add Enemy to the rock if the rock isfalling is true
}

#pragma endregion

