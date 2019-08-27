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

dae::InteractCommand::InteractCommand(GameObject * object)
	: m_object(object)
{
}

dae::InteractCommand::~InteractCommand()
{
	//delete m_object;
}

void dae::InteractCommand::Execute(float deltatime)
{
	m_object->GetComponent<PlayerPengoMovementComponent>()->Interact();
}

dae::StartSoloCommand::StartSoloCommand(GameObject * object)
	: m_object(object)
{
}

dae::StartSoloCommand::~StartSoloCommand()
{
}

void dae::StartSoloCommand::Execute(float deltatime)
{
	m_object->GetComponent<UIMainMenu>()->StartSolo();
}

dae::StartCOOPCommand::StartCOOPCommand(GameObject * object)
	: m_object(object)
{
}

dae::StartCOOPCommand::~StartCOOPCommand()
{
}

void dae::StartCOOPCommand::Execute(float deltatime)
{
	m_object->GetComponent<UIMainMenu>()->StartCoOp();
}

dae::StartVSCommand::StartVSCommand(GameObject * object)
	: m_object(object)
{
}

dae::StartVSCommand::~StartVSCommand()
{
}

void dae::StartVSCommand::Execute(float deltatime)
{
	m_object->GetComponent<UIMainMenu>()->StartVS();
}

dae::QuitCommand::QuitCommand(GameObject * object)
	: m_object(object)
{
}

dae::QuitCommand::~QuitCommand()
{
}

void dae::QuitCommand::Execute(float deltatime)
{
	m_object->GetComponent<UIMainMenu>()->Quit();
}

dae::MoveLeftCommandSnoPlayer::MoveLeftCommandSnoPlayer(GameObject * object)
	: m_object(object)
{
}

dae::MoveLeftCommandSnoPlayer::~MoveLeftCommandSnoPlayer()
{
}

void dae::MoveLeftCommandSnoPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerSnoMovementComponent>()->Move(direction::LEFT);
}

dae::MoveRightCommandSnoPlayer::MoveRightCommandSnoPlayer(GameObject * object)
	: m_object(object)
{
}

dae::MoveRightCommandSnoPlayer::~MoveRightCommandSnoPlayer()
{
}

void dae::MoveRightCommandSnoPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerSnoMovementComponent>()->Move(direction::RIGHT);
}

dae::MoveUpCommandSnoPlayer::MoveUpCommandSnoPlayer(GameObject * object)
	: m_object(object)
{
}

dae::MoveUpCommandSnoPlayer::~MoveUpCommandSnoPlayer()
{
}

void dae::MoveUpCommandSnoPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerSnoMovementComponent>()->Move(direction::UP);
}

dae::MoveDownCommandSnoPlayer::MoveDownCommandSnoPlayer(GameObject * object)
	: m_object(object)
{
}

dae::MoveDownCommandSnoPlayer::~MoveDownCommandSnoPlayer()
{
}

void dae::MoveDownCommandSnoPlayer::Execute(float deltatime)
{
	m_object->GetComponent<PlayerSnoMovementComponent>()->Move(direction::DOWN);
}

dae::InteractSnoCommand::InteractSnoCommand(GameObject * object)
	: m_object(object)
{
}

dae::InteractSnoCommand::~InteractSnoCommand()
{
}

void dae::InteractSnoCommand::Execute(float deltatime)
{
	m_object->GetComponent<PlayerSnoMovementComponent>()->Interact();
}