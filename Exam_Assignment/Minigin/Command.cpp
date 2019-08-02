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

void dae::CollisionCommand::Execute(float , GameObject * , GameObject * )
{
}

