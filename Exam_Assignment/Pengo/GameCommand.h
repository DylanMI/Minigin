#pragma once
#include <Command.h>

class ServiceLocator;
class GameObject;
namespace dae
{
	class GameCommand : public Command
	{
	public:
		virtual ~GameCommand() override;
		virtual void Execute(float deltatime) override;
	};

	class GameCollisionCommand : public Command
	{
	public:
		virtual ~GameCollisionCommand() override;
		virtual void Execute(float deltatime, GameObject* self, GameObject* other) override;
	};

}