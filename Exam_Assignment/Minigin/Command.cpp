#include "MiniginPCH.h"
#include "Command.h"


void dae::Command::Execute(float /*deltatime*/)
{
}

dae::MoveLeftCommand::MoveLeftCommand(GameObject * object)
	: m_object(object)
{
}

void dae::MoveLeftCommand::Execute(float deltatime)
{
	m_object->SetPosition({ m_object->GetTransform().GetPosition().x - 10 * deltatime,m_object->GetTransform().GetPosition().y });
}

dae::MoveRightCommand::MoveRightCommand(GameObject * object)
	: m_object(object)
{
}

void dae::MoveRightCommand::Execute(float deltatime)
{
	m_object->SetPosition({ m_object->GetTransform().GetPosition().x + 10 * deltatime,m_object->GetTransform().GetPosition().y });
}

dae::MoveUpCommand::MoveUpCommand(GameObject * object)
	: m_object(object)
{
}

void dae::MoveUpCommand::Execute(float deltatime)
{
	m_object->SetPosition({ m_object->GetTransform().GetPosition().x,m_object->GetTransform().GetPosition().y - 10 * deltatime });
}

dae::MoveDownCommand::MoveDownCommand(GameObject * object)
	: m_object(object)
{
}

void dae::MoveDownCommand::Execute(float deltatime)
{
	m_object->SetPosition({ m_object->GetTransform().GetPosition().x,m_object->GetTransform().GetPosition().y + 10 * deltatime });
	dae::ServiceLocator::GetInstance().GetAudio().PlaySound(0);
}

dae::FireCommand::FireCommand(GameObject * object)
	: m_object(object)
{
}

void dae::FireCommand::Execute(float /*deltatime*/)
{
}
