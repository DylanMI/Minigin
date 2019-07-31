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

void dae::GameCollisionCommand::Execute(float deltatime, GameObject* self, GameObject* other)
{
}
